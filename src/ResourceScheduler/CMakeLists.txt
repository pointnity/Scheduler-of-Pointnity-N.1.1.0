SET(THRIFT_SOURCE_PREFIX ${CMAKE_SOURCE_DIR}/src/proxy)

SET(JOBS_MANAGER_THRIFT_SOURCE
    ${THRIFT_SOURCE_PREFIX}/JobsManager/gen-cpp/jobs_manager_constants.h 
    ${THRIFT_SOURCE_PREFIX}/JobsManager/gen-cpp/jobs_manager_constants.cpp
    ${THRIFT_SOURCE_PREFIX}/JobsManager/gen-cpp/jobs_manager_types.h
    ${THRIFT_SOURCE_PREFIX}/JobsManager/gen-cpp/jobs_manager_types.cpp
    ${THRIFT_SOURCE_PREFIX}/JobsManager/gen-cpp/JobsManager.h
    ${THRIFT_SOURCE_PREFIX}/JobsManager/gen-cpp/JobsManager.cpp)

ADD_CUSTOM_COMMAND (
    OUTPUT ${JOBS_MANAGER_THRIFT_SOURCE}
    COMMAND thrift --gen cpp -r -o ${CMAKE_SOURCE_DIR}/src/proxy/JobsManager
    ${CMAKE_SOURCE_DIR}/src/proxy/JobsManager/jobs_manager.thrift
)

SET(RESOURCE_SCHEDULER_THRIFT_SOURCE
    ${THRIFT_SOURCE_PREFIX}/ResourceScheduler/gen-cpp/resource_scheduler_constants.h
    ${THRIFT_SOURCE_PREFIX}/ResourceScheduler/gen-cpp/resource_scheduler_constants.cpp
    ${THRIFT_SOURCE_PREFIX}/ResourceScheduler/gen-cpp/resource_scheduler_types.h
    ${THRIFT_SOURCE_PREFIX}/ResourceScheduler/gen-cpp/resource_scheduler_types.cpp
    ${THRIFT_SOURCE_PREFIX}/ResourceScheduler/gen-cpp/ResourceScheduler.h
    ${THRIFT_SOURCE_PREFIX}/ResourceScheduler/gen-cpp/ResourceScheduler.cpp)
ADD_CUSTOM_COMMAND (
    OUTPUT ${RESOURCE_SCHEDULER_THRIFT_SOURCE}
    COMMAND thrift --gen cpp -r -o
${CMAKE_SOURCE_DIR}/src/proxy/ResourceScheduler
    ${CMAKE_SOURCE_DIR}/src/proxy/ResourceScheduler/resource_scheduler.thrift
)

SET(EXECUTOR_THRIFT_SOURCE
    ${THRIFT_SOURCE_PREFIX}/executor/gen-cpp/executor_constants.h
    ${THRIFT_SOURCE_PREFIX}/executor/gen-cpp/executor_constants.cpp
    ${THRIFT_SOURCE_PREFIX}/executor/gen-cpp/executor_types.h
