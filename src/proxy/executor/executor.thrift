//include "../scheduler/scheduler.thrift"
//include "../collector/collector.thrift"

enum TaskEntityState {
    TASKENTITY_WAITING
    TASKENTITY_STARTING
    TASKENTITY_RUNNING
    TASKENTITY_FINISHED
    TASKENTITY_FAILED
    TASKENTITY_MISSED
