/********************************
 FileName: test/submit-job-daemon.cpp
 Version:  0.1
 Description: submit job to JM with daemon
*********************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  
#include <streambuf>  

#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

std::ifstream t("file.txt");  
std::string str((std::istreambuf_iterator<char>(t)),  
                 std::istreambuf_iterator<char>());  
#include "common/clynn/rpc.h"
#include "include/proxy.h"

using namespace std;

static string usage = "./submit-job-daemon  -job_num -max_waiting_job_num -user -xml_file";
static int32_t interval = 2;
static string endpoint = "10.128.85.10:9999";   

vector<int32_t> job_id_list;
vector<int32_t> del_job_id_list;
string result_file = "./result";
string total_result_file = "./total_result";
int64_t finished_task_num = 0;
int64_t failed_task_num = 0;
int64_t task_num = 0;


void* TaskResultProcessor(void* unused) {
    ofstream file_in;
    file_in.open(result_file.c_str());
    file_in << "job number task number status" <<"\n";
    file_in.close();
    while(true) {
        cout << "job list size:"<<job_id_list.size() << endl;
	if(job_id_list.size() == 0) {
	    sleep(1);
	    continue;
	}
	for(vector<int32_t>::iterator it = job_id_list.begin(); it != job_id_list.end(); ++it) {
	    int32_t job_id = *it;
	    vector<TaskStateInfo> task_state_info_list;
	    bool flag = true;
	    try {
        	Proxy<JobsManagerClient> proxy = RpcClient<JobsManagerClient>::GetProxy(endpoint);
        	proxy().GetTaskStateInfo(task_state_info_list, job_id);
    	    } catch (TException &tx) {
        	return NULL;
    	    }

	    if(task_state_info_list.size() == 0) {
		continue;
	    } 
	    for( vector<TaskStateInfo>::iterator it_task = task_state_info_list.begin(); it_task != task_state_info_list.end(); ++it_task) {
    	        if((*it_task).state == 0 || (*it_task).state == 1 || (*it_task).state == 2) {
		    // task is running
		    flag = false;
		    break;
	        }
	    }
		continue;
	    }
	    //open result file 
	    ofstream file_in;
            file_in.open(result_file.c_str(),ios::out|ios::app);

	    string result;
	    stringstream job_id_ss;
	    stringstream task_id_ss;
	    for( vector<TaskStateInfo>::iterator it_1 = task_state_info_list.begin(); it_1 != task_state_info_list.end(); ++it_1) {
		job_id_ss.str("");
		task_id_ss.str("");
		job_id_ss << (*it_1).job_id;
		task_id_ss << (*it_1).task_id;
		if((*it_1).state == 3) {
		    //task is finished
		   result = job_id_ss.str() + "       " + task_id_ss.str() + "      carry out";
		   finished_task_num += 1;
		} else {
		    //task is failed
		   result = job_id_ss.str() + "       " + task_id_ss.str() + "       failure";			
		   failed_task_num += 1;
		}
		cout << "result:" << result << endl;
                file_in << result <<"\n";
		result = "";
            } 
	    file_in.close();
	    del_job_id_list.push_back(job_id);
	}

	for(vector<int32_t>::iterator it = del_job_id_list.begin(); it != del_job_id_list.end(); ++it) {
	    vector<int32_t>::iterator iter = find(job_id_list.begin(), job_id_list.end(), *it);
	    if(iter != job_id_list.end()) {
		job_id_list.erase(iter);
	    }
	}

	//clear delete job id list
	del_job_id_list.clear();	

	//write result to file
	task_num = finished_task_num + failed_task_num;
	stringstream task_num_ss;
