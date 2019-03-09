/********************************
 FileName: common/clynn/thread.cpp


 Version:  0.1
 Description: thread, use a thread to start a func
*********************************/

#include "common/clynn/thread.h"

bool clynn::Thread::Start() {
    int ret = pthread_create(&m_id, NULL, Entry, (void*)this);
    return ret == 0;
}

void clynn::Thread::DoStart() {
    m_is_running = true;
    m_entry();
}

bool clynn::Thread::Join() {
    return pthread_join(m_id, NULL) == 0;
}

void clynn::Thread::Terminate() {
