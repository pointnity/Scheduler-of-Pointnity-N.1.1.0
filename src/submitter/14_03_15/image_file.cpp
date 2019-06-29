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
using std::ios;
using std::ostringstream;

static Logger logger = Logger::getInstance("submitter");

bool ImageFile::CreateImageFile(const string& image_name, const string& image_user, const string& image_local_path){
    //init hdfs
    HDFSMgrI::Instance()->Init();

    //copy local image to hdfs
    const string image_hdfs_path = image_user + "/img/" + image_name;
    if(false == HDFSMgrI::Instance()->CopyFromLocalFile(image_local_path, image_hdfs_path)){
