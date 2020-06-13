#ifndef _log_h
#define _log_h

#include <stdarg.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#ifndef O_CLOEXEC
#define O_CLOEXEC 02000000
#endif

#ifndef F_DUPFD_CLOEXEC
