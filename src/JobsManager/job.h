#ifndef JOBS_MANAGER_JOB_H
#define JOBS_MANAGER_JOB_H

#include <string>
#include <list>
#include <vector>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 5) 
#include <atomic>  // for ubuntu
#else
#include <cstdatomic> // for centos
#endif
