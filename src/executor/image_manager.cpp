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
    const string image_local_path = FLAGS_libvirt_dir + image_name;

    if(FLAGS_debug) {
        LOG4CPLUS_INFO(logger, "image update from hdfs start");
     }
    //open hdfs
    HDFSMgrI::Instance()->OpenConnect();

    if(false == HDFSMgrI::Instance()->CopyToLocalFile(image_hdfs_path, image_local_path)){
        LOG4CPLUS_ERROR(logger, "copy hdfs imge to local error");
        //fprintf(stderr, "copy local image to hdfs error");
        return false;
    }
    //close hdfs
    HDFSMgrI::Instance()->CloseConnect();
    if (FLAGS_debug) {
        LOG4CPLUS_INFO(logger, "image update from hdfs finished");
    }
    //write image attr to conf
    stringstream image_size_ss;
    image_size_ss << image_size;
    string image_attr = image_user + "&" + image_name + "&" + image_size_ss.str();
    string image_attr_conf = FLAGS_libvirt_dir + "conf";

    ofstream file_in;
    file_in.open(image_attr_conf.c_str(),ios::out|ios::app);
    file_in<<image_attr<<"\n";
    file_in.close();
    return true;
}

bool ImageManager::CheckImageAttrFromFile(const string& image) {
    string image_attr_file = FLAGS_libvirt_dir + "conf";
    ifstream in_file(image_attr_file.c_str(), ios::in);
    string image_attr;
    //open file error ?
    if(!in_file){
        LOG4CPLUS_ERROR(logger, "Failed to open image conf file.");
        return false;
    }
    while(!in_file.eof()) {
        in_file >> image_attr;
	if(image_attr == image){
	    return true;
	}
    }
    return false;
}

string ImageManager::GetImageAttrFromFile() {
    bool is_first_attr = true;  
    bool is_first_str = true;
    bool image_flag;
    string image_attr_all; 
    vector<string> image_attr_list;
    string image_attr;
