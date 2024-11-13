#ifndef _POOL_
#define _POOL_

#include "neuron.hpp"
#include <vector>
#include <thread>

namespace DNSM
{
    static std::vector<Neuron> pool;
    static std::mutex pool_access;

    void add_to_pool(Neuron n);

    Neuron* get_from_pool(size_t index);
};

#endif