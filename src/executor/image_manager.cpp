/********************************
 FileName: executor/image_manager.cpp
 Version:  0.1
 Description: image maneger
*********************************/
#include <stdlib.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include "include/classad_attr.h"
#include "executor/image_manager.h"
#include "executor/hdfs_wrapper.h"

DECLARE_string(image_path);
DECLARE_string(libvirt_dir);
DECLARE_bool(debug);

using log4cplus::Logger;
using namespace std;

static Logger logger = Logger::getInstance("executor");

bool ImageManager::ExecutorUpdateImage(const string& image_user, const string& image_name, const int32_t image_size) {
    //get image path
    const string image_hdfs_path = "/lynn/" + image_user + "/img/" + image_name;
    const string image_hdfs_path = "/lynn/" + image_user + "/img/" + image_name;
