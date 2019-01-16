#!/bin/bash
function usage()
{
    echo "$0 op"
    echo "op start/stop"
    exit 1
}

if [ $# -ne 1 ]; then
    usage
    exit 1
fi

if [ $1 == "start" ]; then
   cd ../zookeeper
   ./server1/zookeeper-3.4.5/bin/zkServer.sh start
