#include "thread_pool.hpp"

void DNSM::ThreadPool::thread_pool_init()
{
    _running = true;
    for (auto &node : __free_workers)
    {
        node._th = std::thread(
            [this, &node]()
            {
                while (_running)
                {
                    // try and fetch a new task to execute
                    if (fetch_task(&node))
                    {
                        // we have a task to do
                    }
                }
            });
    }
}

void DNSM::ThreadPool::thread_pool_terminate()
{
    std::atomic_store(&_running, false);
    for (auto &node : __free_workers)
    {
        if (node._th.joinable())
            node._th.join();
    }
}

bool DNSM::ThreadPool::fetch_task(ThreadPoolNode *node)
{
    bool res = true;
    _fetch_lock.lock();
    if (_tasks.empty())
        res = false;
    else
    {
        node->task = _tasks.front()._this;
        _tasks.pop();
    }
    _fetch_lock.unlock();
    return res;
}

void DNSM::ThreadPool::add_tasks(ThreadPoolTask *task)
{
    _fetch_lock.lock(); // The same lock
    _tasks.push(std::move(*task));
    _fetch_lock.unlock();
}