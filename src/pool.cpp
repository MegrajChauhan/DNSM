#include "pool.hpp"

void DNSM::add_to_pool(Neuron n)
{
    pool_access.lock();
    pool.push_back(n);
    pool_access.unlock();
}

DNSM::Neuron* DNSM::get_from_pool(size_t index)
{
    pool_access.lock();
    if (index >= pool.size())
       return nullptr; // this will probably never happen
    pool_access.unlock();
    return &pool[index];
}