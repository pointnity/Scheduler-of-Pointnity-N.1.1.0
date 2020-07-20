/********************************
 FileName: executor/handler.cpp
 Version:  0.1
 Description: handler for event
*********************************/

#include "executor/handler.h"

using std::tr1::bind;

Handler::~Handler() {
    delete m_work_thread;
    delete m_work_thread;
