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
    string job_type = argv[3];

    // task_num 
    int32_t task_num = atoi(argv[4]);
    if (task_num <= 0) {
        cout << "Usage is wrong." << endl;
        cout << "Usage is: " << usage << endl;
        cout << "Task_num must be a positive interger." << endl;
        return -1;
    }

    cout << "submit job, job_type:" << job_type << ", task_num:" << task_num << endl;
    string endpoint = "192.168.10.80:9999"; // hy
    // string endpoint = "192.168.120.88:9999"; // iie

    // build job ClassAd 
    ClassAd ad;
    // overview
