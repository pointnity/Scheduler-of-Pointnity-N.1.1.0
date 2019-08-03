/********************************
 FileName: test/scheduler/submit-job.cpp
 Version:  0.1
 Description: submit a job to scheduler (with xml file)
*********************************/

#include <iostream>
#include <string>
#include <string.h>

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include "common/clynn/rpc.h"
#include "include/proxy.h"
#include "include/classad_attr.h"

using namespace std;

static string usage = "./submit-job group_name prio job_type task_num";

int main(int argc, char ** argv) {
    if(argc != 5) {
        cout << "Usage is wrong." << endl;
        cout << "Usage is: " << usage << endl;
        return -1;
    }
    
    // group name
    string name = argv[1];
    string group_name = "Group " + name;

    // priority
    int32_t prio = atoi(argv[2]);
    
    // job_type
