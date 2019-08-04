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
