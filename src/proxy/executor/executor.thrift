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
