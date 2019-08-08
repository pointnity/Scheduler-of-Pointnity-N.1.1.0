/********************************
 FileName: test/collector/negotiater.cpp
 Version:  0.1
 Description: match a job  (with xml file)
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

static string usage = "./submit-job job_type task_num";

int main(int argc, char ** argv) {
    if(argc != 3) {
        cout << "Usage is wrong." << endl;
