#include <stdio.h>
#include <zookeeper/zookeeper.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <map>
#include <boost/algorithm/string.hpp>
#include <classad/classad.h>
#include <classad/classad_distribution.h>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "common/clynn/rwlock.h"
#include "include/proxy.h"
#include "common/clynn/rpc.h"

using std::string;
