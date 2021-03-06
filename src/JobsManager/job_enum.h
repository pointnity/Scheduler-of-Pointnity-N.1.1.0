#ifndef JOBS_MANAGER_JOB_ENUM_H
#define JOBS_MANAGER_JOB_ENUM_H

enum JobType {
   JOB_TYPE_BATCH,
   JOB_TYPE_SERVICE,
   JOB_TYPE_CRON,
}; 

enum JobRawPrio {
   JOB_RAW_PRIO_PRIVILEGE,
   JOB_RAW_PRIO_HIGH,
   JOB_RAW_PRIO_ORDINARY,
   JOB_RAW_PRIO_LOW,
};

enum SchedModel {
    DEFAULT_MODEL,
    WIDE_DISTRIBUTION,
};

enum JobQueueNum {
   JOB_QUEUE_NAVIGATING,
   JOB_QUEUE_PRIVILEGE_WAIT,
   JOB_QUEUE_HIGH_WAIT,
   JOB_QUEUE_ORDINARY_WAIT,
   JOB_QUEUE_LOW_WAIT,
};

enum JobState {
   JOB_WAITING,
   JOB_SCHEDULING,
   JOB_RUNNING,
   JOB_FINISHED,
   JOB_FAILED,
};

enum TaskState {
   TASK_WAITING,
   TASK_STARTING,
   TASK_RUNNING,
   TASK_FINISHED,
   TASK_FAILED,
   TASK_MISSED,
};

enum JMEventType {
    TASK_STATE_EVENT,
    TASK_ACTION_EVENT,
    IMAGE_EVENT,
    APP_EVENT,
}; 

enum JobError {
    E_JOB_ATTR = 1,
    E_JOB_NO_CLASSAD,
    E_JOB_TYPE,
};

#endif
