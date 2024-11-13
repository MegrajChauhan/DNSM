#include "neuron.hpp"

void DNSM::Neuron::init_neuron()
{
    Randomizer rand;
    
    sociability = rand.generate_double(0, 1);
    antisociability = 1.0 - sociability;

    openness = rand.generate_double(0, 1);
    shyness = 1.0 - openness;

    activity = rand.generate_double(0, 1);

    stimulation_threshold = rand.generate_double(0,1);

    incoming_connections = 0;
    outgoing_connections = 0;
    killed_connections = 0;
    times_input_received = 0;
    identifying_mark = 0;
}

void DNSM::Neuron::mark_neuron(size_t mark)
{
    identifying_mark = mark;
}