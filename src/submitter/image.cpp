/*******************************
 File name: submitter/image.cpp
 Version:  0.1
 Description: image 
*********************************/

#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "submitter/hdfs_wrapper.h"
#include "submitter/image.h"
#include "include/classad_attr.h"
#include "include/proxy.h"

#include "common/rapidxml/rapidxml.hpp"
#include "common/rapidxml/rapidxml_utils.hpp"
#include "common/clynn/rpc.h"

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include <gflags/gflags.h>

using log4cplus::Logger;
using std::string;
using std::vector;

using rapidxml::file;
using rapidxml::xml_document;
using rapidxml::xml_node;
using rapidxml::xml_attribute;

DECLARE_string(JobsManager_endpoint);
DECLARE_bool(first_create_image);

static Logger logger = Logger::getInstance("submitter");

bool Image::CreateImage(const string& xml_path){
    //read xml to init
    std::cout<< "init config start:"<<xml_path<<std::endl;
    m_xml_path = xml_path;
    if(false == Init()){
        LOG4CPLUS_ERROR(logger, "read xml init error");
	fprintf(stderr, "read xml init error\n");
        return false;
    }
    if(true == FLAGS_first_create_image){
        //check local image
        string image_local_path = m_local_path + "/" + m_name;
	std::cout<< "image_local_path:"<<image_local_path<<std::endl;
        if(access(image_local_path.c_str(), F_OK) == -1) {
            LOG4CPLUS_ERROR(logger, "image file no found");
	    fprintf(stderr, "image file no found\n");
            return false;
	}       
 
        //send image file to HDFS
        std::cout<< "upload image to hdfs start"<<std::endl;
        if(false == SendImagetoHDFS()){
            LOG4CPLUS_ERROR(logger, "send image file to hdfs  error");
            fprintf(stderr, "send image file to hdfs  error\n");
	    return false;
        }
        std::cout<< "upload image from hdfs finish"<<std::endl;
    }
