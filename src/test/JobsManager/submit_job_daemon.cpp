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
