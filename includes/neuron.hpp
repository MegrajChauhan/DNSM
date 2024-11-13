#ifndef _NEURON_
#define _NEURON_

#include "conf.hpp"
#include "utils.hpp"
#include <string>
#include <vector>

namespace DNSM
{
    typedef double __neuron_field_t;
    typedef double __path_field_t;

    class Neuron;

    /**
     * @path_activation_value: Similar to the Neuron's @stimulation_threshold but for a path
     * 
     */
    struct Path
    {
        Neuron *receiver;
        Neuron *sender;

        __path_field_t path_activation_value;

        // The path is what will hold the signal that is passed to the receiver
        __path_field_t sent_signal;
    };

    /**
     * Neuron needs to be a heavy class
     * @sociability: How social is the neuron? Higher value means it will easily build connections.
     * @antisociability: How anti-social is the neuron? Higher value means it will hesitate to build connections.
     * @openness: How open is the neuron? Higher value means it will easily break old bonds(open to new bonds)
     * @shyness: The opposite of @openness. Higher value results in bonds that will not break as easily.
     * @activity: Activity of the neuron decides how active it is. Higher value means it will produce stronger signals
     * @stimulation_threshold: The threshold that must be reached in order for the neuron to fire
     */
    class Neuron
    {
        __neuron_field_t sociability;
        __neuron_field_t antisociability;
        __neuron_field_t openness;
        __neuron_field_t shyness;
        __neuron_field_t activity;
        __neuron_field_t stimulation_threshold;

        // Some debugging and tracking variables
        size_t incoming_connections;
        size_t outgoing_connections;
        size_t killed_connections;   // how many connections have been killed already?
        size_t times_input_received; // how many times was the neuron activated?
        size_t identifying_mark;     // The "name" of the neuron

        std::vector<Path> connections;

        // We don't store the incoming calls because we don't have to

    public:
        Neuron() = default;

        void init_neuron();

        void mark_neuron(size_t mark);
    };
};

#endif