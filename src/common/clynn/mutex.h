/********************************
 FileName: common/clynn/metux.h


 Version:  0.1
 Description: metux, lock for multi thread
*********************************/

#ifndef COMMON_MUTEX_H
#define COMMON_MUTEX_H

#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

namespace clynn {

    class Mutex {
        public:
            Mutex() {
                CheckError("Mutex::Mutex", pthread_mutex_init(&m_lock, NULL));
