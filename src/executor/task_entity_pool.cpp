/********************************
 FileName: executor/task_entity_pool.cpp
 Version:  0.1
 Description: the pool of taskentitys
*********************************/

#include <assert.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "executor/task_entity_pool.h"
#include "executor/dispatcher.h"


using log4cplus::Logger;
using clynn::ReadLocker;
using clynn::WriteLocker;

static Logger logger = Logger::getInstance("executor");

DECLARE_bool(debug);
// TODO just for test
void TaskEntityPool::PrintAll() {
    ReadLocker locker(m_lock);
    printf("task_entity_pool.cpp\n");
    printf("************ Task Entity ************\n");
    for (map<TaskID, TaskPtr>::iterator it = m_task_map.begin();
         it != m_task_map.end(); ++it) {
        printf("taskentity job_id:%d, task_id:%d\n", (it->first).job_id, (it->first).task_id);
    }    
    printf("**************************************\n");
}
