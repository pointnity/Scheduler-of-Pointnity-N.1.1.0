/********************************
 FileName: common/clynn/rpc.h


 Version:  0.1
 Description: rpc with thrift 
*********************************/

#ifndef COMMON_RPC_H
#define COMMON_RPC_H

#include <concurrency/ThreadManager.h>
#include <concurrency/PosixThreadFactory.h>
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <server/TThreadPoolServer.h>
#include <server/TThreadedServer.h>
