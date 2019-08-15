SET(THRIFT_SOURCE_PREFIX ${CMAKE_SOURCE_DIR}/src/proxy)

SET(TEST_THRIFT_SOURCE
    ${THRIFT_SOURCE_PREFIX}/test/gen-cpp/test_constants.h
    ${THRIFT_SOURCE_PREFIX}/test/gen-cpp/test_constants.cpp
    ${THRIFT_SOURCE_PREFIX}/test/gen-cpp/test_types.h
    ${THRIFT_SOURCE_PREFIX}/test/gen-cpp/test_types.cpp
    ${THRIFT_SOURCE_PREFIX}/test/gen-cpp/Test.h
    ${THRIFT_SOURCE_PREFIX}/test/gen-cpp/Test.cpp)
