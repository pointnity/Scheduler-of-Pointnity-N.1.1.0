/********************************
 FileName: jobs_manager/jobs_manager_service.cpp


 Version:  0.1
 Description: jobs_manager service
*********************************/
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "JobsManager/jobs_manager_service.h"
#include "JobsManager/job_parser.h"
#include "JobsManager/task.h"
#include "JobsManager/event.h"
#include "JobsManager/dispatcher.h"
#include "JobsManager/job_pool.h"
#include "JobsManager/group_pool.h"

using log4cplus::Logger;

static Logger logger = Logger::getInstance("JobsManager");

void JobsManagerService::SubmitJob(SubmitJobResult& result, const string& job_xml) {
    JobParser job_parser;
    int32_t ret = job_parser.SubmitNewJob(job_xml, result.job_id); 
    result.error_num = ret;
