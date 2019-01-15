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
