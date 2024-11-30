#ifndef _FUNCS_
#define _FUNCS_

#include <initializer_list>

#define activation_func(name) double name(std::initializer_list<double> args)

// a list of all activation functions
namespace DNSM
{
    class Neuron;

    /**
     * The activation functions are going to be complex given we have to 
     * incorporate all of the properties of the neuron into the mix.
     */

    // the args will be (<Neuron's properties in sequence>, Input signal)
    typedef double (*__activationfn_t)(std::initializer_list<double>);

    // mathematical functions
    activation_func(simple_add);  // simple add and mapped to range[0,1]
    activation_func(simple_mul);  // simple multiply and mapped to range[0,1]
    activation_func(simple_div);  // simple divide and mapped to range[0,1]
    activation_func(simple_sub);  // simple sub and mapped to range[0,1]
    activation_func(simple_exp);  // simple exponentiation and mapped to range[0,1]
    activation_func(simple_log);  // simple log and mapped to range[0,1]
    activation_func(simple_sqrt); // simple square root and mapped to range[0,1]
    activation_func(simple_mod);  // simple mod mapped to range [0, 1]

    activation_func(ReLU); // if input signal is positive, input signal mapped to range[0,1] else 0

    // some other simple functions
    activation_func(simple_threshold_check); // check if input > stimulation_threshold

    // some custom functions
    activation_func(sociability_activation); // using the property of the neuron
    activation_func(shyness_activation);
    activation_func(signal_decay); // The input signal decays over time
    activation_func(signal_boost); // input signal strengthens over time

};

// #include "neuron.hpp"

#endif