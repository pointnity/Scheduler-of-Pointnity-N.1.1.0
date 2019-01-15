#!/bin/bash
function usage()
{
    echo "$0 num"
    exit 1
}

if [ $# -ne 1 ]; then
    usage
    exit 1
