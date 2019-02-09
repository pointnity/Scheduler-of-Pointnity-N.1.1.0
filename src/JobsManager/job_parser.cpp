/********************************
 FileName: JobsManager/job_parser.cpp


 Version:  0.1
 Description: parse job from xml file, init job and tasks
*********************************/

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "common/rapidxml/rapidxml.hpp"
#include "common/rapidxml/rapidxml_utils.hpp"
#include "common/rapidxml/rapidxml_print.hpp"
#include "common/clynn/string_utility.h"

#include "iostream"
#include "include/classad_attr.h"
#include "JobsManager/jobs_manager_service.h"
#include "JobsManager/job_enum.h"
#include "JobsManager/job_parser.h"
#include "JobsManager/job_pool.h"
#include "JobsManager/group_pool.h"
#include "JobsManager/batch_job.h"

using log4cplus::Logger;
using namespace rapidxml;
using std::cout;

static Logger logger = Logger::getInstance("JobsManager");

#define MAX_WEIGHT 100
#define MAX_WEIGHT_N -100

JobParser::JobParser() {
    m_job_classad_ptr = ClassAdPtr(new ClassAd());
    m_job_id = 0;
    m_errno = 0;
}

JobParser::~JobParser() {
   //Empty the generated task Classad
   m_taskad_list.clear();
}

int32_t JobParser::SubmitNewJob(const string& job_xml, int32_t job_id) {
    LOG4CPLUS_INFO(logger, "submitting a new job:" << std::endl << job_xml);

    if (!ParseJobAd(job_xml)) {
        LOG4CPLUS_ERROR(logger, "Failed to submit a new job:" << job_xml);
        return m_errno;
    }

    JobPtr job_ptr = CreateJobPtr();
    if (NULL == job_ptr) {
        return m_errno;
    }

    // test TODO 
    job_ptr->PrintAllTasks();

    JobPoolI::Instance()->InsertIfAbsent(job_ptr);
    // test TODO
    JobPoolI::Instance()->PrintAll();
    NewJobList::Instance()->PushBack(job_ptr);
    return 0;
}

void JobParser::PrintAllTasks() {
    printf("-------- tasks --------\n");
    string str_classad = ClassAdComplement::AdTostring(m_job_classad_ptr);
    printf("job classad: %s\n", str_classad.c_str());

    for (list<TaskAdPtr>::iterator it = m_taskad_list.begin();
         it != m_taskad_list.end(); ++it)
    {
         // hard constraint
         ClassAdPtr hard_ptr = (*it)->taskad_hard_constraint;
         string str_hard_classad = ClassAdComplement::AdTostring(hard_ptr);
         printf("task hard classad: %s\n", str_hard_classad.c_str());
         // soft constraint list
         for (list<ClassAdPtr>::iterator inner_it = (*it)->soft_constraint_list.begin();
              inner_it != (*it)->soft_constraint_list.end(); ++ inner_it)
         {
             ClassAdPtr soft_ptr = *inner_it;
             string str_soft_classad = ClassAdComplement::AdTostring(soft_ptr);
             printf("task soft classad: %s\n", str_soft_classad.c_str());
         }
    }

    // constraints among tasks
    for (list<EdgePtr>::iterator it = m_edge_list.begin();
         it != m_edge_list.end(); ++it)
    {
        printf("start: %d, end: %d, weight: %d\n", (*it)->GetStart(), (*it)->GetEnd(), (*it)->GetWeight());
    }
    printf("---------------------\n");
