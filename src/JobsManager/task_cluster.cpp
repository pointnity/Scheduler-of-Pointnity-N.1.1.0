/********************************
 FileName: JobsManager/task.cpp


 Version:  0.1
 Description: task, include ClassAd m_taskad_hard_constraint and list<ClassAd> m_soft_constraint_list
*********************************/

#include "JobsManager/task.h"

using clynn::ReadLocker;
using clynn::WriteLocker;

TaskStatus Task::GetTaskStatus() {
