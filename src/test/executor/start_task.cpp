#include <iostream>
#include <string>
#include <string.h>

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include "common/clynn/rpc.h"
#include "include/proxy.h"
#include "include/classad_attr.h"

using namespace std;

static string usage = "./start_task job_id task_id vnc_port vm_type";

int main(int argc, char ** argv) {
    if(argc != 5) {
        cout << "Usage is wrong." << endl;
        cout << "Usage is: " << usage << endl;
        return -1;
    }

    // job id
    int32_t job_id = atoi(argv[1]);
    if (job_id <= 0) {
        cout << "Usage is wrong." << endl;
        cout << "Usage is: " << usage << endl;
        return -1;
    }

    // task id
    int32_t task_id = atoi(argv[2]);
    if (task_id <= 0) {    
        cout << "Usage is wrong." << endl;
        cout << "Usage is: " << usage << endl;
        return -1;
    }

    // vnc port
    int32_t vnc_port = atoi(argv[3]);
    if (vnc_port < 0) {
        cout << "Usage is wrong." << endl;
        cout << "Usage is: " << usage << endl;
        return -1;
    }

    // vm type
    string vm_type = argv[4];
    int32_t vm_t = 0;
    bool is_run = false;
    if ("" == vm_type) {
        cout << "Usage is wrong." << endl;
        cout << "Usage is: " << usage << endl;
        return -1;
    } else if ("KVM" == vm_type) {
        vm_t = 1;
        is_run = false; 
    } else if ("LXC" == vm_type) {
        vm_t = 2;
        is_run = true;
    } else {
        cout << "No the VM Type '" << vm_type << "'." << endl;
    }
    
    cout << "start task, job_id:" << job_id << ", task_id:" << task_id << endl;
    //string endpoint = "192.168.11.51:9997"; // hy
    // string endpoint = "192.168.120.88:9999"; // iie
    string endpoint = "10.138.80.66:9997";
