/********************************
 FileName: JobsManager/work_thread.cpp


 Version:  0.2
 Description: work threads
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <tr1/functional>

#include "JobsManager/job_pool.h"
#include "JobsManager/group_pool.h"
#include "JobsManager/job_master.h"

using log4cplus::Logger;
using std::tr1::bind;
using std::tr1::placeholders::_1;

static Logger logger = Logger::getInstance("JobsManager");

void* NewJobThread(void* ununsed) {
    while (true) {
        JobPtr job;
        NewJobList::Instance()->PopFront(&job);
        job->SetWaitTime();
        if (!GroupPoolI::Instance()->AddJobToWaitQueue(job)){
            job->SetState(JOB_FAILED);
            JobPoolI::Instance()->HistoryJobListPushBack(job);
        }
    }
    return NULL;
}

/* void* JobSelectorThread(void* unused) {
    while(true) {
        JobSelector selector;
        if (selector.SelectJob() == false) {
            // TODO
