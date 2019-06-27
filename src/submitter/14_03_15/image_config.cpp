/*******************************
 File name: submitter/image_config.cpp
 Author:   Tangxuehai
 Version:  0.1
 Description: image config 
*********************************/

#include <strstream>
#include <vector>
#include "submitter/image_config.h"
#include "include/classad_attr.h"
#include "include/proxy.h"
#include "common/clynn/rpc.h"
#include "common/rapidxml/rapidxml.hpp"
#include "common/rapidxml/rapidxml_utils.hpp"

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

using log4cplus::Logger;
using std::string;
