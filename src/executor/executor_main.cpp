/********************************
 FileName: executor/executor.cpp
 Version:  0.1
 Description: executor main
*********************************/

#include <iostream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/fileappender.h>
