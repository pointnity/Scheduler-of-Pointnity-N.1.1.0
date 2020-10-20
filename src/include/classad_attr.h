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
static const string ATTR_RPC_RUNNING = "RPC_RUNNING";

// task appinfo
static const string ATTR_APP_ID = "APP_ID";
static const string ATTR_APP_NAME = "APP_NAME";
static const string ATTR_APP_FILE = "APP_FILE";

// -- outside vm, hdfs
static const string ATTR_APP_SRC_PATH = "SRC_PATH";
static const string ATTR_APP_OUT_DIR = "OUT_DIR";
// -- inside vm, windows or linux
static const string ATTR_INSTALL_DIR = "INSTALL_DIR";
static const string ATTR_EXE_PATH = "EXE_PATH";
static const string ATTR_ARGUMENT = "ATTR_ARGUMENT";
static const string ATTR_STOP_PATH = "STOP_PATH";
static const string ATTR_OUT_DIR = "EXE_OUT_DIR";
static const string ATTR_EXE = "EXE";


/// @brief: Register MachineInfo
static const string ATTR_Machine = "Machine";
static const string ATTR_MachineType = "MachineType";
static const string ATTR_Shelf = "Shelf";
