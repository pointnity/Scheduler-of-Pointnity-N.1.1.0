#include <stdio.h>
#include <zookeeper/zookeeper.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <classad/classad.h>
#include <classad/classad_distribution.h>
#include <boost/shared_ptr.hpp>
#include "common/clynn/rwlock.h"
#include "include/proxy.h"
#include "common/clynn/rpc.h"

using std::string;
using boost::shared_ptr;
using clynn::RWLock;
using clynn::ReadLocker;
using clynn::WriteLocker;

string master_endpoint = "127.0.0.1:9998";

    int32_t main(int argc, char* argv[]){
    string ad2 = "[ IP = \"127.0.0.2\"; Port = 8888 ]";
    string ad3 = "[ IP = \"127.0.0.3\"; Port = 7777 ]";
