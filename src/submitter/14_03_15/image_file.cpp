/*******************************
 File name: submitter/image_file.cpp
 Version:  0.1
 Description: image file
*********************************/

#include <fstream>
#include <iostream>
#include <sstream>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "submitter/image_file.h"
#include "include/hdfs.h"
#include "hdfs_wrapper.h"

using log4cplus::Logger;
using std::string;
using std::ifstream;
