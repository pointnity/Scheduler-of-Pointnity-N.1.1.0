#include <iostream>
#include <string>
#include <string.h>

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include "common/clynn/rpc.h"
#include "include/proxy.h"
#include "include/classad_attr.h"

using namespace std;

static string usage = "./stop_task job_id task_id";

int main(int argc, char ** argv) {
    if(argc != 3) {
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
