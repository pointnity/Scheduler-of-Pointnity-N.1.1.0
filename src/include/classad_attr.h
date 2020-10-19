/********************************
 FileName: include/classad_attr.h
 Version:  0.1
 Description: attributes of classad
*********************************/

#ifndef INCLUDE_CLASSAD_ATTR_H
#define INCLUDE_CLASSAD_ATTR_H
#include <string>

using std::string;

/// @brief: TaskInfo
// task info overview
static const string ATTR_JOB_ID = "JOB_ID";
static const string ATTR_TASK_ID = "TASK_ID";
static const string ATTR_VMTYPE = "VMTYPE";
static const string ATTR_IS_RUN = "IS_RUN";
static const string ATTR_USER = "USER";

// task vminfo
static const string ATTR_MEMORY = "MEMORY";
static const string ATTR_VCPU = "VCPU";
static const string ATTR_IP = "IP";
static const string ATTR_PORT = "PORT";
static const string ATTR_OS = "OS";
// -- only for kvm
static const string ATTR_IMG = "IMG";
static const string ATTR_ISO = "ISO";
static const string ATTR_SIZE = "SIZE";
static const string ATTR_VNC_PORT = "VNC_PORT";
