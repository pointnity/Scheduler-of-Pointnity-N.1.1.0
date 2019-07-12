#include <stdio.h>
#include <zookeeper/zookeeper.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include "common/classad/classad_complement.h"

using std::string;

int32_t main(int argc, char* argv[]){
    string         classad_string = "[a = 1; b = \"Cardini\"]";
    string         str = "[ ATTR_JOB_ID = 18; ATTR_TASK_ID = 1; ATTR_VMHB_CPU = 0.000000; ATTR_VMHB_MEMORY = 0.456332; ATTR_VMHB_BYTES_IN = 170008; ATTR_VMHB_BYTES_OUT = 27905; ATTR_VMHB_STATE = \"APP_RUNNING\" ]";
