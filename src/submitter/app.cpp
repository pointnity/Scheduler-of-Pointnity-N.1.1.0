/*******************************
 File name: submitter/app.cpp
 Version:  0.1
 Description: app manager for submitter
*********************************/

#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "submitter/hdfs_wrapper.h"
#include "submitter/app.h"
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

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using log4cplus::Logger;
using std::string;
using std::vector;

using rapidxml::file;
using rapidxml::xml_document;
using rapidxml::xml_node;
using rapidxml::xml_attribute;

DECLARE_string(JobsManager_endpoint);

static Logger logger = Logger::getInstance("submitter");

bool App::CreateApp(const string& xml_path){
