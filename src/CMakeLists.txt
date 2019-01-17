SET(SRC ".")

INCLUDE_DIRECTORIES(
    ${THRIFT_INCLUDE_PATH}
    # ${JNI_INCLUDE_DIRS}  # for jni.h, jni.h use in /usr/local/include/hdfs/hdfs.h
    ${SRC}/)
# LINK_DIRECTORIES(${JVM_LIBRARAY_DIR})
