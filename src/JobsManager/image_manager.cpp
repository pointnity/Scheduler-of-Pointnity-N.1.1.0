/********************************
 FileName: JobsManager/image_manager.cpp


 Version:  0.1
 Description: image maneger
*********************************/
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include <iostream>
#include <vector>
#include <string>

#include "JobsManager/image_manager.h"
#include "common/clynn/rpc.h"
#include "include/proxy.h"

DECLARE_string(image_path);
DECLARE_string(resource_scheduler_endpoint);
using log4cplus::Logger;
using namespace std;
