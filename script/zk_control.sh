#!/bin/bash
function usage()
{
    echo "$0 op"
    echo "op start/stop"
    exit 1
}

if [ $# -ne 1 ]; then
