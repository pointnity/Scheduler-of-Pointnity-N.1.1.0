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
    for (std::map<std::string, std::string>::iterator it
         = one_map.begin(); it != one_map.end(); ++it) {
        std::cout << it->first << "-----" << it->second << std::endl;
    }
}


TEST(TestZookeeperCommon, TestCreateNode) {
    ZookeeperCommon my_zk;
    int rt = my_zk.Init("xaec-test_for_zk_common");
    if (rt < 0) {
        LOG(ERROR) << "connect zk failed.";
    } else {
        EXPECT_EQ(rt, 0);
        rt = my_zk.CreateNodeForce("/zk/xaec/tborg/xaec-test_for_zk_common/tns/mavisluo");
        std::cout << "=============================" << my_zk.GetZKPrefix() << std::endl;
        // sleep(20);
        EXPECT_EQ(rt, 0);


        rt = my_zk.CreateNode("/zk/xaec/tborg/xaec-test_for_zk_common"
                              "/tns/mavisluo/no_node/no_node");
        EXPECT_EQ(rt, -1);
        /// delete the node that created just now
