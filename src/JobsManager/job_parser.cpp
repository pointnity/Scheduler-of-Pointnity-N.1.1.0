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
