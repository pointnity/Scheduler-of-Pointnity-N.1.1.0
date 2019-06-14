//include "../scheduler/scheduler.thrift"
//include "../collector/collector.thrift"

enum TaskEntityState {
    TASKENTITY_WAITING
    TASKENTITY_STARTING
    TASKENTITY_RUNNING
    TASKENTITY_FINISHED
    TASKENTITY_FAILED
    TASKENTITY_MISSED
}

enum VMType {
    VM_UNKNOWN
    VM_KVM
    VM_LXC
}

enum AppState {
    APP_WAITING
    APP_STARTING
    APP_RUNNING 
    APP_FINISHED 
    APP_MISSED 
    APP_FAILED 
}

enum EventType {
    TASK_STATE_EVENT 
    TASK_ACTION_EVENT 
