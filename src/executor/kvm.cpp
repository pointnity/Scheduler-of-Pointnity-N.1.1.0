/********************************
 FileName: executor/kvm.cpp
 Version:  0.1
 Description: kvm, inherit from vm
*********************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "common/rapidxml/rapidxml.hpp"
#include "common/rapidxml/rapidxml_utils.hpp"
#include "common/rapidxml/rapidxml_print.hpp"
#include "common/clynn/rpc.h"

#include <classad/classad.h>
#include <classad/classad_distribution.h>
#include "include/classad_attr.h"

#include "include/proxy.h"
#include "executor/hdfs_wrapper.h"
#include "executor/kvm.h"
#include "executor/task_entity_pool.h"
#include "executor/resource_manager.h"
#include "executor/dispatcher.h"
#include "executor/image_manager.h"
#include "executor/vm_pool.h"

using std::cout;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::endl;
using namespace rapidxml;
using namespace std;
using log4cplus::Logger;
using clynn::WriteLocker;
