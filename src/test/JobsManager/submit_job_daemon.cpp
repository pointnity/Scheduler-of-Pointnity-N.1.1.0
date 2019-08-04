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
