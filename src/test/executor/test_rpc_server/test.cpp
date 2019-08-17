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
    //Rpc<ExecutorService, ExecutorProcessor>::Listen(port);

    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
    // is root?
    if (geteuid() != 0) {
        fprintf(stderr, "Executor: must be run as root, or sudo run it.\n");
        return EXIT_FAILURE;
