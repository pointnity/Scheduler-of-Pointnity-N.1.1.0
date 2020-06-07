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

    /**
     * Some utility decls used in libhdfs.
     */

    typedef int32_t   tSize; /// size of data for read/write io ops
    typedef time_t    tTime; /// time type in seconds
    typedef int64_t   tOffset;/// offset within the file
    typedef uint16_t  tPort; /// port
    typedef enum tObjectKind {
        kObjectKindFile = 'F',
        kObjectKindDirectory = 'D',
    } tObjectKind;


    /**
     * The C reflection of org.apache.org.hadoop.FileSystem .
     */
    typedef void* hdfsFS;

    
    /**
     * The C equivalent of org.apache.org.hadoop.FSData(Input|Output)Stream .
     */
    enum hdfsStreamType
    {
        UNINITIALIZED = 0,
        INPUT = 1,
        OUTPUT = 2,
        void* file;
        enum hdfsStreamType type;
    };
    typedef struct hdfsFile_internal* hdfsFile;
      

    /** 
     * hdfsConnectAsUser - Connect to a hdfs file system as a specific user
     * Connect to the hdfs.
     * @param host A string containing either a host name, or an ip address
     * of the namenode of a hdfs cluster. 'host' should be passed as NULL if
     * you want to connect to local filesystem. 'host' should be passed as
     * 'default' (and port as 0) to used the 'configured' filesystem
     * (core-site/core-default.xml).
     * @param port The port on which the server is listening.
     * @param user the user name (this is hadoop domain user). Or NULL is equivelant to hhdfsConnect(host, port)
     * @return Returns a handle to the filesystem or NULL on error.
     */
     hdfsFS hdfsConnectAsUser(const char* host, tPort port, const char *user);


    /** 
     * hdfsConnect - Connect to a hdfs file system.
     * Connect to the hdfs.
     * @param host A string containing either a host name, or an ip address
     * of the namenode of a hdfs cluster. 'host' should be passed as NULL if
     * you want to connect to local filesystem. 'host' should be passed as
     * 'default' (and port as 0) to used the 'configured' filesystem
     * (core-site/core-default.xml).
     * @param port The port on which the server is listening.
     * @return Returns a handle to the filesystem or NULL on error.
     */
     hdfsFS hdfsConnect(const char* host, tPort port);


    /** 
     * hdfsDisconnect - Disconnect from the hdfs file system.
     * Disconnect from hdfs.
     * @param fs The configured filesystem handle.
     * @return Returns 0 on success, -1 on error.  
     */
    int hdfsDisconnect(hdfsFS fs);
        

    /** 
     * hdfsOpenFile - Open a hdfs file in given mode.
     * @param fs The configured filesystem handle.
     * @param path The full path to the file.
     * @param flags - an | of bits/fcntl.h file flags - supported flags are O_RDONLY, O_WRONLY (meaning create or overwrite i.e., implies O_TRUNCAT), 
     * O_WRONLY|O_APPEND. Other flags are generally ignored other than (O_RDWR || (O_EXCL & O_CREAT)) which return NULL and set errno equal ENOTSUP.
     * @param bufferSize Size of buffer for read/write - pass 0 if you want
     * to use the default configured values.
     * @param replication Block replication - pass 0 if you want to use
     * the default configured values.
     * @param blocksize Size of block - pass 0 if you want to use the
     * default configured values.
     * @return Returns the handle to the open file or NULL on error.
     */
    hdfsFile hdfsOpenFile(hdfsFS fs, const char* path, int flags,
                          int bufferSize, short replication, tSize blocksize);


    /** 
     * hdfsCloseFile - Close an open file. 
     * @param fs The configured filesystem handle.
     * @param file The file handle.
     * @return Returns 0 on success, -1 on error.  
     */
    int hdfsCloseFile(hdfsFS fs, hdfsFile file);


    /** 
     * hdfsExists - Checks if a given path exsits on the filesystem 
     * @param fs The configured filesystem handle.
     * @param path The path to look for
     * @return Returns 0 on success, -1 on error.  
     */
    int hdfsExists(hdfsFS fs, const char *path);


    /** 
     * hdfsSeek - Seek to given offset in file. 
     * This works only for files opened in read-only mode. 
     * @param fs The configured filesystem handle.
     * @param file The file handle.
     * @param desiredPos Offset into the file to seek into.
     * @return Returns 0 on success, -1 on error.  
     */
    int hdfsSeek(hdfsFS fs, hdfsFile file, tOffset desiredPos); 


    /** 
     * hdfsTell - Get the current offset in the file, in bytes.
     * @param fs The configured filesystem handle.
     * @param file The file handle.
     * @return Current offset, -1 on error.
     */
    tOffset hdfsTell(hdfsFS fs, hdfsFile file);


    /** 
     * hdfsRead - Read data from an open file.
     * @param fs The configured filesystem handle.
     * @param file The file handle.
     * @param buffer The buffer to copy read bytes into.
     * @param length The length of the buffer.
     * @return Returns the number of bytes actually read, possibly less
     * than than length;-1 on error.
     */
    tSize hdfsRead(hdfsFS fs, hdfsFile file, void* buffer, tSize length);


    /** 
     * hdfsPread - Positional read of data from an open file.
     * @param fs The configured filesystem handle.
     * @param file The file handle.
     * @param position Position from which to read
     * @param buffer The buffer to copy read bytes into.
     * @param length The length of the buffer.
     * @return Returns the number of bytes actually read, possibly less than
     * than length;-1 on error.
     */
    tSize hdfsPread(hdfsFS fs, hdfsFile file, tOffset position,
                    void* buffer, tSize length);


    /** 
     * hdfsWrite - Write data into an open file.
     * @param fs The configured filesystem handle.
     * @param file The file handle.
     * @param buffer The data.
     * @param length The no. of bytes to write. 
     * @return Returns the number of bytes written, -1 on error.
     */
    tSize hdfsWrite(hdfsFS fs, hdfsFile file, const void* buffer,
                    tSize length);


    /** 
     * hdfsWrite - Flush the data. 
     * @param fs The configured filesystem handle.
     * @param file The file handle.
     * @return Returns 0 on success, -1 on error. 
     */
    int hdfsFlush(hdfsFS fs, hdfsFile file);


    /**
     * hdfsAvailable - Number of bytes that can be read from this
     * input stream without blocking.
     * @param fs The configured filesystem handle.
     * @param file The file handle.
     * @return Returns available bytes; -1 on error. 
     */
    int hdfsAvailable(hdfsFS fs, hdfsFile file);


    /**
     * hdfsCopy - Copy file from one filesystem to another.
     * @param srcFS The handle to source filesystem.
     * @param src The path of source file. 
     * @param dstFS The handle to destination filesystem.
     * @param dst The path of destination file. 
     * @return Returns 0 on success, -1 on error. 
     */
    int hdfsCopy(hdfsFS srcFS, const char* src, hdfsFS dstFS, const char* dst);


    /**
     * hdfsMove - Move file from one filesystem to another.
     * @param srcFS The handle to source filesystem.
     * @param src The path of source file. 
     * @param dstFS The handle to destination filesystem.
     * @param dst The path of destination file. 
     * @return Returns 0 on success, -1 on error. 
     */
    int hdfsMove(hdfsFS srcFS, const char* src, hdfsFS dstFS, const char* dst);


    /**
     * hdfsDelete - Delete file. 
     * @param fs The configured filesystem handle.
     * @param path The path of the file. 
     * @return Returns 0 on success, -1 on error. 
     */
    int hdfsDelete(hdfsFS fs, const char* path);


    /**
