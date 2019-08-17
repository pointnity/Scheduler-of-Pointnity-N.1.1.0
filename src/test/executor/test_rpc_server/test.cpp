/********************************
 FileName: executor/executor.cpp
 Version:  0.1
 Description: executor main
*********************************/

#include <iostream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "common/clynn/rpc.h"
#include "service.h"

using std::string;
using std::cout;
using std::endl;
using std::auto_ptr;


// executor
int ExecutorEntity(int argc, char **argv) {
    int port = 9997; 
    RpcServer<TestService, TestProcessor>::Listen(port);
    //int port = 9999; 
