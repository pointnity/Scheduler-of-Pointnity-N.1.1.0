/********************************
 FileName: submitter/config.cpp
 Version:  0.1
 Description: config for submitter
*********************************/

#include "gflags/gflags.h"

DEFINE_string(JobsManager_endpoint, "127.0.0.1:9999", "JobsManager endpoint");
DEFINE_string(xml_path, "", "xml path");
DEFINE_int32(hdfs_port, 9000, "hdfs port");
DEFINE_string(hdfs_host, "localhost", "hdfs host");
DEFINE_bool(first_create_image, true, "image is first create or not");

DEFINE_string(object, "Image", "JobManager endpoint");
