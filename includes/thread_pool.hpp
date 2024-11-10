#ifndef _THREAD_POOL_
#define _THREAD_POOL_

#include <thread>
#include <queue>
#include <memory>
#include <array>
// #include <atomic>
#include "neuron.hpp"
#include "conf.hpp"

namespace DNSM
{
    struct ThreadPoolNode
    {
        std::thread _th;
        std::shared_ptr<Neuron> task;
    };

    struct ThreadPoolTask
    {
        std::shared_ptr<Neuron> _this;
    };

    class ThreadPool
    {
        std::queue<ThreadPoolTask> _tasks;
        std::atomic_bool _running;
        std::mutex _fetch_lock;

        bool fetch_task(ThreadPoolNode *node);

    public:
        static std::array<ThreadPoolNode, _THREAD_POOL_LEN_> __free_workers;
        static std::array<ThreadPoolNode, _THREAD_POOL_LEN_> __working_threads;

        void thread_pool_init();

        void add_tasks(ThreadPoolTask *task);

        void thread_pool_terminate();
    };
}

#endif