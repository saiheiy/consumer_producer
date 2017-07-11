#ifndef SRC_SYNCHRONIZEDQUEUE_H
#define SRC_SYNCHRONIZEDQUEUE_H

#include <PT.h>
#include <bslmt_lockguard.h>
#include <bslmt_mutex.h>

#include <queue>
//#include <algorithm>

using namespace BloombergLP;

template <typename T>
class SynchronizedQueue {
public:
    bool empty() {
        bslmt::LockGuard<bslmt::Mutex> guard(&m_mutex);
        return m_queue.empty();
    }

    std::size_t size(){
        bslmt::LockGuard<bslmt::Mutex> guard(&m_mutex);
        return m_queue.size();
    }

    const T& front() {
        bslmt::LockGuard<bslmt::Mutex> guard(&m_mutex);
        return m_queue.front();
    }

    template <typename T1>
    void enqueue(T1&& item) {
        bslmt::LockGuard<bslmt::Mutex> guard(&m_mutex);
        m_queue.emplace(std::forward<T1>(item));
    }

    void dequeue() {
        bslmt::LockGuard<bslmt::Mutex> guard(&m_mutex);
        m_queue.pop();
    }

    void rotateOne() {
        bslmt::LockGuard<bslmt::Mutex> guard(&m_mutex);
        if ( m_queue.size() < 1){
            return;
        }
        m_queue.emplace(std::move(m_queue.front()));
        m_queue.pop();
    }


private:
    std::queue<T> m_queue;
    bslmt::Mutex m_mutex;
};


#endif //SRC_SYNCHRONIZEDQUEUE_H
