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
