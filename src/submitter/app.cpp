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
