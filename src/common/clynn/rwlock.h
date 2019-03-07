/********************************
 FileName: common/clynn/rwlock.h


 Version:  0.1
 Description: the class about pthread_rwlock_t, lock of read and write
*********************************/

#ifndef COMMON_RWLOCK_H
#define COMMON_RWLOCK_H

#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

namespace clynn {

    class RWLock {
        public:
            RWLock() {
                CheckError("Rwlock::Rwlock", pthread_rwlock_init(&m_lock, NULL));
            }

            ~RWLock() {
                pthread_rwlock_destroy(&m_lock);
            }

            void ReadLock() {
                CheckError("RWLock::ReadLock", pthread_rwlock_rdlock(&m_lock));
            }

            void WriteLock() {
                CheckError("RWLock::WriteLock", pthread_rwlock_wrlock(&m_lock));
            }

            void Unlock() {
