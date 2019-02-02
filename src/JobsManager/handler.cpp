/********************************
 FileName: JobsManager/handler.cpp


 Version:  0.1
 Description: handler for event
*********************************/

#include "JobsManager/handler.h"

using std::tr1::bind;

Handler::~Handler() {
    delete m_work_thread;
}

// start the thread
void Handler::Start() {
    Thread::ThreadFunc func = bind(&Handler::Handle, this);
    m_work_thread = new Thread(func);
    m_work_thread->Start();
}

void Handler::Handle() {
    while (true) {
        // pop and get event, then handle it
        EventPtr event;      
        m_event_queue.PopFront(&event);
        // virtual func
