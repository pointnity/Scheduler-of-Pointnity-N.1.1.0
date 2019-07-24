// =============================================================================
// Version: 0.1
// Author: mavisluo 
// Revision: 43791 
// Description:test for zookeeper
// Id: zk_common_test.cpp 
// =============================================================================

#include <gtest/gtest.h>
#include <gflags/gflags.h>
#include <map>
#include "tborg/conf_manager/zk_common.h"
#include "tborg/conf_manager/watcher.h"

void PrintMap(std::map<std::string, std::string> one_map) {
