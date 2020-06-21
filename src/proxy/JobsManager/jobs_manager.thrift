struct SubmitJobResult {
    1: i32 job_id,
    2: i32 error_num,
}

struct TaskStateInfo {
    1:i32 job_id,
    2:i32 task_id,
    3:i32 state,
    4:string machine_ip,
