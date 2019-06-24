/*******************************
 File name: submitter/job.cpp
 Version:  0.1
 Description: job manager for submitter
*********************************/

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "submitter/job.h"
#include "include/proxy.h"
#include "common/clynn/rpc.h"

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include <gflags/gflags.h>

using log4cplus::Logger;
using namespace std;

DECLARE_string(JobsManager_endpoint);

static Logger logger = Logger::getInstance("submitter");

bool Job::CreateJob(const string& xml_path){
    // xml file to string
    ifstream in(xml_path);
    string xml_content((istreambuf_iterator<char>(in)),istreambuf_iterator<char>());
    in.close();

    struct SubmitJobResult result;
    std::cout<< "submit job start"<<std::endl;
    try {
        Proxy<JobsManagerClient> proxy = RpcClient<JobsManagerClient>::GetProxy(FLAGS_JobsManager_endpoint);
        proxy().SubmitJob(result, xml_content);
    } catch (TException &tx) {
	fprintf(stderr, "rpc error to create job\n");
        return false;
    }
    std::cout<< "submit job finished"<<std::endl;
    std::cout <<"SubmitJobResult:"<<result.error_num << std::endl;
    return true;
}


bool Job::QueryJob(const int32_t job_id){
    std::cout<< "query job id:"<<job_id<<std::endl;
    vector<TaskStateInfo> task_state_info_list;
    try {
        Proxy<JobsManagerClient> proxy = RpcClient<JobsManagerClient>::GetProxy(FLAGS_JobsManager_endpoint);
        proxy().GetTaskStateInfo(task_state_info_list, job_id);
    } catch (TException &tx) {
