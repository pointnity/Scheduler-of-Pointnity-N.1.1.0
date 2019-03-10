#ifndef COMMON_CLYNN_TIMER_H
#define COMMON_CLYNN_TIMER_H

#include <unistd.h>
#include <sys/time.h>

namespace clynn {

    class Timer {
    public:
       explicit Timer(bool auto_start = true) {
           m_is_running = auto_start; 
