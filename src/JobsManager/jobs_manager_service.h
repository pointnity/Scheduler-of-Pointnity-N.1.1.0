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
