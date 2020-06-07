#ifndef LIBHDFS_HDFS_H
#define LIBHDFS_HDFS_H

#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include <jni.h>

#ifndef O_RDONLY
#define O_RDONLY 1
#endif

#ifndef O_WRONLY 
#define O_WRONLY 2
#endif

#ifndef EINTERNAL
#define EINTERNAL 255 
#endif


/** All APIs set errno to meaningful values */
#ifdef __cplusplus
extern  "C" {
#endif
#
    /**

