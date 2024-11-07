#ifndef _THREAD_POOL_
#define _THREAD_POOL_

#include <thread>
#include <queue>
#include <memory>
#include "neuron.hpp"

namespace DNSM
{
    struct ThreadPoolTask
    {
        std::shared_ptr<Neuron> _this; // the neuron should have all of the stages 
    };

    class ThreadPool
    {
    };
};

#endif