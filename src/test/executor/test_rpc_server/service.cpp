/********************************
 FileName: executor/service.cpp
 Version:  0.1
 Description: executor service
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include "service.h"
#include <iostream>

// test, hello world
int32_t TestService::Helloworld() {
    printf("Hello world\n");
    return 0;
