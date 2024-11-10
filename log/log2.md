# Attempt 2: Better Design
This design change already solves many of the complicated problem encountered previously. Immediately, we find one issue with this design as well.

# Problem
1. **Preserving state:** When, in one cycle, multiple neurons push the same neuron on the queue for the cascading signal, we will have to preserve the state of the neuron in both threads.
The neuron might be expected to be in some state but if the state changes due to one signal pass then the neuron may enter an unexpected state for the second signal pass. 

# Solution
1. **Potential Solution to Problem 1:** If we choose a __First Come First Served__ architecture for the signal passing then this can be mitigated but this will demand another component
that would do the secure updation of the network during which the network becomes useless. We have to remove race conditions at all costs.