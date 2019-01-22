#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include "common/clynn/timer.h"
#include "common/clynn/rpc.h"
#include "common/classad/classad_complement.h"
#include "JobsManager/job_matcher.h"
#include "proxy/ResourceScheduler/gen-cpp/ResourceScheduler.h"

DECLARE_string(resource_scheduler_endpoint);

using log4cplus::Logger;
using clynn::Timer;
static Logger logger = Logger::getInstance("JobsManager");

int32_t JobMatcher::MatchTaskList(list<TaskMatchInfo>& task_match_list) {
    if(task_match_list.empty()) {
        return 1;
    }

    bool match_one_task = false;
    for (list<TaskMatchInfo>::iterator it = task_match_list.begin();
        it != task_match_list.end(); ++it) {
        // hard constraint
        string taskad_hard = it->taskad_hard_constraint;
        if (taskad_hard.empty()) { 
           continue;
        }
        vector<string> soft_list;
        for (list<string>::iterator soft_it = it->soft_constraint_list.begin();
             soft_it != it->soft_constraint_list.end(); ++ soft_it) 
        {
            soft_list.push_back(*soft_it);
        }

        string result = "Unscheduled";
        if (SendRequestConstraint(taskad_hard, soft_list, result) != 0) {
            // TODO
            // continue;
            return -1;
        }
        if ("" == result) {
            // TODO
            return -1;
        }
        it->es_address = result;
        printf("Match result:\n job_id: %d, task_id: %d, result: %s\n", it->job_id, it->task_id, it->es_address.c_str());
        /* match_one_task = true;
        if(result.size() <= 1) {
           
        } */
    }
    return 0;
}

int32_t JobMatcher::SendRequest(const string& classad, string& match_result) {
