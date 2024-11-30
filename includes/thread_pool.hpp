#ifndef _THREAD_POOL_
#define _THREAD_POOL_

#include <thread>
#include <queue>
#include <array>
// #include <atomic>
#include "utils.hpp"
#include "neuron.hpp"
#include "pool.hpp"
#include "conf.hpp"

namespace DNSM
{
    struct ThreadPoolNode
    {
        std::thread _th;
        size_t task;
    };

    struct ThreadPoolTask
    {
        size_t _this;
        Path *incoming;
    };

    class ThreadPool
    {
        std::queue<ThreadPoolTask> _tasks;
        std::atomic_bool _running;
        std::mutex _fetch_lock;
        std::array<ThreadPoolNode, _THREAD_POOL_LEN_> __free_workers;
        std::array<ThreadPoolNode, _THREAD_POOL_LEN_> __working_threads;

        bool fetch_task(ThreadPoolNode *node);

    public:

        void thread_pool_init();

        void add_tasks(ThreadPoolTask task);

        void thread_pool_terminate();
    };
}

#endif