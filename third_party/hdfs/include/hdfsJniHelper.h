#ifndef LIBHDFS_JNI_HELPER_H
#define LIBHDFS_JNI_HELPER_H

#include <jni.h>
#include <stdio.h>

#include <stdlib.h>
#include <stdarg.h>
#include <search.h>
#include <pthread.h>
#include <errno.h>

#define PATH_SEPARATOR ':'


/** Denote the method we want to invoke as STATIC or INSTANCE */
typedef enum {
