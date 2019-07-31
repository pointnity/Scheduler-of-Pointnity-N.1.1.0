// =============================================================================
// Version: 0.1
// Author: mavisluo 
// Revision: 17158 
// Description:test for zookeeper
// Id：zk_common_test.cpp
// =============================================================================

#include <gtest/gtest.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <gflags/gflags.h>
#include <map>
#include <list>
#include <string>
#include <vector>
#include "tborg/conf_manager/zk_common.h"
#include "tborg/include/get_hostip.h"
#include "common/config/cflags.hpp"
#include "tborg/collector/collector_conf.h"
#include "tborg/conf_manager/dynamic_configuration.h"
#include "tborg/conf_manager/conf_manager.h"
#include "common/system/concurrency/atomic/atomic.hpp"

/// ip:port of zk servers
DEFINE_string(zk_servers, "", "ip:port of zk servers");

std::string test_node = "/zk/xaec/tborg/" + FLAGS_cluster_name +
                        "/tns/mavisluo";

class MyEnvironment : public testing::Environment
{
    public:
        virtual void SetUp() {
            std::cout << "MyEnvironment SetUP" << std::endl;
            FLAGS_cluster_name = "xaec-comprehensive_test_zk_" + get_hostip();
            /// create test nodes
            ConfManager my_zk;

            int rt = my_zk.Init(FLAGS_cluster_name, FLAGS_zk_servers);
            if (rt < 0) {
                std::cout << "tns_test init failed." << std::endl;
                return;
            } else {
                my_zk.CreateDefaultCluster();
                /// set some config items
                my_zk.SetOneConf("global", "collector_endpoint", "10.6.207.227:9618");
                my_zk.SetOneConf("global", "scheduler_endpoint", "10.6.207.227:9618");
                my_zk.SetOneConf("global", "scheduler_http_endpoint", "10.6.207.227:9618");
                my_zk.SetOneConf("global", "scheduler_endpoint_for_submitter", "10.6.207.227:9618");
                my_zk.SetOneConf("collector", "borg_dbhost", "10.6.207.228");
            }
        }

        virtual void TearDown() {
            std::cout << "MyEnvironment TearDown" << std::endl;
            ZookeeperCommon my_zk;
            int rt = my_zk.Init(FLAGS_cluster_name, FLAGS_zk_servers);
            if (rt < 0) {
                std::cout << "zk server init failed." << std::endl;
            } else {
                /// delete all test ndoes
                my_zk.DeleteNodeForceRecursively("/zk/xaec/tborg/" + FLAGS_cluster_name);
            }
        }
};

void PrintMap(std::map<std::string, std::string> one_map) {
    for (std::map<std::string, std::string>::iterator it
         = one_map.begin(); it != one_map.end(); ++it) {
        std::cout << it->first << "-----" << it->second << std::endl;
    }
}

/// test: create a zk node
TEST(TestZookeeperCommon, TestCreateNode) {
    ZookeeperCommon my_zk;
    int rt = my_zk.Init(FLAGS_cluster_name, FLAGS_zk_servers);
    if (rt < 0) {
        LOG(ERROR) << "connect zk failed.";
    } else {
        EXPECT_EQ(rt, 0);
        /// create a normal node, the result will be 0
        rt = my_zk.CreateNode(test_node);
        EXPECT_EQ(rt, 0);
        rt = my_zk.CheckPathExist(test_node);
        EXPECT_EQ(rt, 0);
        /// if you create a node already exists, the result is also 0
        rt = my_zk.CreateNode(test_node);
        EXPECT_EQ(rt, 0);
        rt = my_zk.CheckPathExist(test_node);
        EXPECT_EQ(rt, 0);
        /// if you create a node which has no parent, the result is -1
        rt = my_zk.CreateNode(test_node + "/no_parent/node");
        EXPECT_EQ(rt, -1);
        rt = my_zk.CheckPathExist(test_node + "/no_parent/node");
        EXPECT_EQ(rt, -1);
        /// delete the node that created just now
        rt = my_zk.DeleteNodeForceRecursively(test_node);
        EXPECT_EQ(rt, 0);
        rt = my_zk.CheckPathExist(test_node);
        EXPECT_EQ(rt, -1);
    }
}

/// test: check if a node(path) exists
TEST(TestZookeeperCommon, CheckPathExist) {
    ZookeeperCommon my_zk;
    int rt = my_zk.Init(FLAGS_cluster_name, FLAGS_zk_servers);
    if (rt < 0) {
        LOG(ERROR) << "connect zk failed.";
    } else {
        EXPECT_EQ(rt, 0);
        /// create a node
        rt = my_zk.CreateNode(test_node);
        EXPECT_EQ(rt, 0);
        rt = my_zk.CheckPathExist(test_node);
        EXPECT_EQ(rt, 0);
        /// delete the node
        rt = my_zk.DeleteNode(test_node);
        EXPECT_EQ(rt, 0);
        rt = my_zk.CheckPathExist(test_node);
        EXPECT_EQ(rt, -1);
    }
}
