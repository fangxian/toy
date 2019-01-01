//
// Created by yfx on 19-1-1.
//

#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include <thread>
#include <functional>
#include <vector>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
using namespace std;

//function template can match all function
typedef function<void()> Task;
class ThreadPool {
public:
    ThreadPool(int thread_num, int MaxQueueSize = 20);
    ~ThreadPool();
    void AddTask(Task t);
    Task ConsumeTask();
    void RunTask();
    bool IsFull();
    void Stop();
private:
    vector<thread> m_threads;
    int m_threadNums;
    bool m_brunning;

    deque<Task> m_tasks;
    int m_MaxDequeSize;
    mutex m_TaskMutex;

    condition_variable m_notFull;
    condition_variable m_notEmpty;
    unique_lock<mutex> m_uniqueLock_notFull;
    unique_lock<mutex> m_uniqueLock_notEmpty;
    mutex m_Mutex_notFull;
    mutex m_Mutex_notEmpty;
};


#endif //THREADPOOL_THREADPOOL_H
