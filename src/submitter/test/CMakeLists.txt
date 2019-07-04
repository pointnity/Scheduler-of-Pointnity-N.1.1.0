SET(THRIFT_SOURCE_PREFIX ${CMAKE_SOURCE_DIR}/src/proxy)
  
SET(MASTER_THRIFT_SOURCE
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/master_constants.h
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/master_constants.cpp
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/master_types.h
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/master_types.cpp
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/Master.h
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/Master.cpp)
ADD_CUSTOM_COMMAND (
    OUTPUT ${MASTER_THRIFT_SOURCE}
    COMMAND thrift --gen cpp -r -o ${CMAKE_SOURCE_DIR}/src/proxy/master
    ${CMAKE_SOURCE_DIR}/src/proxy/master/master.thrift
)

INCLUDE_DIRECTORIES(
$ENV{HADOOP_HOME}/src/c++/libhdfs
)
INCLUDE_DIRECTORIES(
$ENV{JAVA_HOME}/include
)
INCLUDE_DIRECTORIES(
$ENV{JAVA_HOME}/include/linux
)

INCLUDE_DIRECTORIES(
$ENV{JAVA_HOME}/jre/lib/amd64/server
)
INCLUDE_DIRECTORIES(
