/********************************
 FileName: resource_scheduler/work_thread.h


 Last Update: 
 Version:  0.1
 Description: work thread
*********************************/

#include <stdlib.h>
#include <gflags/gflags.h>

#include "resource_scheduler_engine.h"

DECLARE_int32(hb_interval);
// thread, machine monitor
void* MachineMonitorProcessor(void* unused) {
