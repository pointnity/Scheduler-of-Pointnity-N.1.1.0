/********************************
 FileName: JobsManager/JobsManager_service.h


 Version:  0.1
 Description: JobsManager service
*********************************/

#ifndef SRC_JOBS_MANAGER_SERVICE_H
#define SRC_JOBS_MANAGER_SERVICE_H

#include <vector>
#include "proxy/JobsManager/gen-cpp/JobsManager.h"

using std::string;
using std::vector;

class JobsManagerService : public JobsManagerIf {
public:
    void SubmitJob(SubmitJobResult& result, const string& job_xml);
    void GetJobId(vector<int32_t>& job_id_list);
    void GetTaskStateInfo(vector<TaskStateInfo>& task_state_info_list, int32_t job_id);
    int32_t GetWaitJobNumByGroupName(const string& group);
    void GetGroupStateInfo(GroupStateInfo& group_info, const string& group_name); 

