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
