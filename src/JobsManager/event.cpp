/********************************
 FileName: JobsManager/event.cpp


 Version:  0.1
 Description: event, and its handler
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "JobsManager/event.h"
#include "JobsManager/image_manager.h"
#include "JobsManager/app_manager.h"
#include "JobsManager/job_pool.h"


using log4cplus::Logger;

static Logger logger = Logger::getInstance("JobsManager");

// update image
bool ImageEvent::Handle() {
    string name = GetName();
    string user = GetUser();
    int32_t size = GetSize();
    bool is_update_all = GetIs_update_all();
    return ImageMgrI::Instance()->UpdateImage(user, name, size, is_update_all);
}

// Create app
bool AppEvent::Handle() {
    string name = GetName();
    string user = GetUser();
    return AppMgrI::Instance()->CreateApp(user, name);
}

// start task
bool StartTaskEvent::Handle() {
    // TaskPtr task_ptr = JobPoolI::Instance()->GetTask(m_job_id, m_task_id);
