/********************************
 FileName: JobsManager/group_pool.cpp


 Version:  0.1
 Description: Pool of Groups
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "common/rapidxml/rapidxml.hpp"
#include "common/rapidxml/rapidxml_utils.hpp"
#include "common/rapidxml/rapidxml_print.hpp"
#include "JobsManager/group_pool.h"

using std::vector;
using log4cplus::Logger;
using clynn::ReadLocker;
using clynn::WriteLocker;
using namespace rapidxml;

static Logger logger = Logger::getInstance("JobsManager");

// In the Rapidxml process, you cannot operate to store other pointers, although they do not appear to be connected.To avoid strange bugs,

struct sGroup {
