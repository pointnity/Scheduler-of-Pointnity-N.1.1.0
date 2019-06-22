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
