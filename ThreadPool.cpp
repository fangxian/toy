//
// Created by yfx on 19-1-1.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(int thread_num, int MaxQueueSize)
    :m_threadNums(thread_num),
    m_brunning(true),
    m_MaxDequeSize(MaxQueueSize)
{
    for(int i=0; i < thread_num; i++)
    {
        //thread t = thread(bind(&ThreadPool::RunTask, this));
        m_threads.push_back(thread(bind(&ThreadPool::RunTask, this)));
    }
}

ThreadPool::~ThreadPool()
{
    while(!m_tasks.empty())
    {
        ;
    }
    m_brunning = false;
    m_notFull.notify_all();
    m_notEmpty.notify_all();
    for(auto iter=m_threads.begin(); iter != m_threads.end(); iter++)
    {
        if(iter->joinable())
            iter->join();
    }
}

void ThreadPool::AddTask(Task t)
{
    unique_lock<mutex> ulk(m_Mutex_notFull);

    while(IsFull() && m_brunning)
    {
        //usleep(10);
        m_notFull.wait(ulk);
    }

    m_tasks.push_back(std::move(t));
    ulk.unlock();
    m_notEmpty.notify_one();
}

Task ThreadPool::ConsumeTask()
{
    m_TaskMutex.lock();
    unique_lock<mutex> ulk(m_Mutex_notEmpty);
    while(m_tasks.empty() && m_brunning)
    {
        //usleep(10);
        m_notEmpty.wait(ulk);
    }
    Task t;
    if(m_tasks.size() != 0)
    {
        t = m_tasks.front();
        m_tasks.pop_front();
        m_notFull.notify_one();
    }
    ulk.unlock();
    m_TaskMutex.unlock();
    return t;

}

void ThreadPool::RunTask()
{
    while(m_brunning)
    {
        Task task = ConsumeTask();
        if(task)
        {
            task();
        }
    }
}

bool ThreadPool::IsFull()
{
    if(m_tasks.size() == m_MaxDequeSize)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ThreadPool::Stop()
{
    m_brunning = false;
}