/********************************
 FileName: executor/hdfs_wrapper.h
 Version:  0.1
 Description: hdfs wrapper
*********************************/

#ifndef SRC_HDFS_WRAPPER_H
#define SRC_HDFS_WRAPPER_H

#include <string>
// #include <hdfs/hdfs.h>
#include "common/hdfs/hdfs.h"
#include "common/clynn/singleton.h"

// TODO
// user ACL

class HDFSWrapper {
public:
    bool OpenConnect();
    bool CloseConnect();
    bool CopyFromLocalFile(const string src, const string dst);
    bool CopyToLocalFile(const string src, const string dst); 
