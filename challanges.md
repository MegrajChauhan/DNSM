# Discarded Inputs
Getting to the point, consider the following:
**N1->N2->N3->N7->N10->N4**

Also consider the following path:
**N1->N3->N9->N13->N4**

Both leads to _N4_ in the end and N4 needs both the inputs to fire properly hence it is necessary for N4 to wait for the next path to give it the input.
The problem with this is that this example is just a simple demonstration and we cannot know for sure how many more cycles must N4 wait for. In this
example, N4 needs to wait just 1 cycle more but the challange lies in the fact that the paths are variable in length. In most cases we cannot even tell
if the connection leading to the neuron needs to be waited upon. For eg: **...->N3->N7->N3->...**. Here, N3 will have to wait for itself and thus end up
stalling the entire network. 

## Potential Solution
One solution is to keep track of the path lengths relative to the input neurons. By doing so we solve the first problem of getting all inputs but the second
problem will require another solution. By knowing the path lengths, we can see how long a neuron must wait. This solution, however, adds more problems than
it solves. The most important is that we need a lot memory. The second problem is finding the length of the path itself. The receiving neuron can have, in
theory, infinite connections from just one neuron. That neuron maybe connected to the input neuron in paths that will be hard to trace. For eg: There may be
dead paths i.e Paths that never fire because the Path activation threshold can never be crossed. 

This solution is not worth it to implement.

## A Gamble
Though receiving all inputs might be ideal for a more accurate and intelligent network but that is virtually impossible. What do we do? Stick to the ground.
The main purpose of this model was to try and mimic a biological neuron as closely as my knowledge allows and if my knowledge is correct then a biological
neuron never waits for input connections, it just passes the signals if the signal has a certain strength.
Thus, we will do the same and gamble on it.