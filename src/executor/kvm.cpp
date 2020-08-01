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

#include <classad/classad.h>
