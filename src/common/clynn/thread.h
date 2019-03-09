/********************************
 FileName: common/clynn/thread.h


 Version:  0.1
 Description: thread, use a thread to start a func
*********************************/

#ifndef SRC_COMMON_THREAD_H
#define SRC_COMMON_THREAD_H

#include <pthread.h>

#include <tr1/memory>
#include <tr1/functional>

using std::tr1::function;
using std::tr1::placeholders::_1;
using std::tr1::placeholders::_2;

namespace clynn
{
    class Thread
    {
    public:
        typedef function<void()> ThreadFunc;
   
    public:
        Thread() : m_entry(NULL),
                   m_context(NULL),
                   m_param(0),
                   m_is_running(false) {}

        Thread(ThreadFunc entry, void* context = NULL, unsigned long long param = 0) : m_entry(entry), 
       m_context(context),
