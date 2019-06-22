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
