/********************************
 FileName: executor_monitor/restart_executor.cpp
 Version:  0.1
 Description: restart executor 
*********************************/
#include <stdlib.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>


#include "executor_monitor/restart_executor.h"
