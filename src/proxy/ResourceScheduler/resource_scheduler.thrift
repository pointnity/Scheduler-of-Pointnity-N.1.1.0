enum MachineError {
    MACHINE_ERROR_SUCCESS,
    MACHINE_ERROR_CLASSAD_SYNTAX,
    MACHINE_ERROR_ATTR,
    MACHINE_ERROR_NUM_LIMIT,
    MACHINE_ERROR_NOT_FOUND,
}

struct MultiD_Resource {
    1: i32 total_cpu,
    2: i32 total_memory,
    3: i32 total_disk,
}

enum RSEventType {
    MACHINE_UPDATE_EVENT,
MACHINE_DELETE_EVENT
}


service ResourceScheduler {
    string GetCurVersion();
    i32 RegistMachine(1: string ip, 3: string version),
    i32 UpdateMachine(1: string heartbeat_ad),
    i32 NewUpdateMachine(1: string heartbeat_ad, 2: list<string> task_list),
