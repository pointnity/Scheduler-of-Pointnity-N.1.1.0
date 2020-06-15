#ifndef __namespace_h
#define __namespace_h

#include <syscall.h>
#include <sched.h>

#ifndef CLONE_FS
#  define CLONE_FS                0x00000200
#endif
#ifndef CLONE_NEWNS
#  define CLONE_NEWNS             0x00020000
#endif
#ifndef CLONE_NEWUTS
