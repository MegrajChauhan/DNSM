#ifndef _NEURON_
#define _NEURON_

#include "conf.hpp"
#include <string>
#include <vector>

namespace DNSM
{
    typedef double __neuron_field_t;

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

    public:
        Neuron();
    };
};

#endif