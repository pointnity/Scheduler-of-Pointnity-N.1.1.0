#!/bin/bash
function usage()
{
    echo "$0 num"
    exit 1
}

if [ $# -ne 1 ]; then
    usage
    exit 1
fi

cd ../zookeeper
mkdir -p server1/data server1/dataLog server1/logs
mkdir -p server2/data server2/dataLog server2/logs
mkdir -p server3/data server3/dataLog server3/logs

tar -xvzf zookeeper-3.4.5.tar.gz
cp -r zookeeper-3.4.5 server1
