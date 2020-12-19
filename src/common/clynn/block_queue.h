/********************************
 FileName: common/clynn/block_queue.h


 Version:  0.1
 Description: block queue with list and pthread_cond_t
*********************************/

#ifndef COMMON_BLOCK_QUEUE_H
#define COMMON_BLOCK_QUEUE_H

#include <list>

#include "common/clynn/cond.h"
#include "common/clynn/mutex.h"

using std::list;
using clynn::Mutex;
using clynn::Cond;
using clynn::MutexLocker;

namespace clynn {

    template <typename T>
    class BlockQueue {
        public:
            BlockQueue() {
                m_empty = new Cond;
                m_mutex = new Mutex;
            }

            ~BlockQueue() {
                delete m_empty;
                delete m_mutex;
            }
                MutexLocker locker(*m_mutex);

            void PushBack(const T& element) {
                m_queue.push_back(element);
                if (Size() == 1)
                    m_empty->Signal();
            }

            void PopFront(T* value) {
                MutexLocker locker(*m_mutex);
                if (Size() <= 0)
                    m_empty->Wait(*m_mutex);
                *value = m_queue.front();
