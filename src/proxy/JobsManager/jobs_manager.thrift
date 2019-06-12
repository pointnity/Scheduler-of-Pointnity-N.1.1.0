struct SubmitJobResult {
    1: i32 job_id,
    2: i32 error_num,
}

struct TaskStateInfo {
    1:i32 job_id,
    2:i32 task_id,
    3:i32 state,
    4:string machine_ip,
    5:i32 restart_times,
    6:i32 failed_times,
    7:i32 timeout_times,
    8:i32 missed_times,    
}

struct GroupStateInfo {
    1:string name,
