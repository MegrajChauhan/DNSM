#ifndef _DEFIN_
#define _DEFIN_

#include "neuron.hpp"
#include <algorithm>
#include <cmath>
#include <random>
#include <ctime>

namespace defin
{
    namespace activation
    {
        // all activation functions
        void _simple_add(neuron::Neuron *n); // this just adds all the input signals

        void _simple_product(neuron::Neuron *n); // multiply all the input signals

        void _simple_max(neuron::Neuron *n); // the maximum of the input signals

        void _simple_max_min_diff(neuron::Neuron *n); // difference between the max and min of the input signal

        void _simple_rand_times_max(neuron::Neuron *n); // get a random number between 0 and 1 and multiply with the maximum

        void _simple_product_sum_diff(neuron::Neuron *n); // difference of the sum and the product

        void _simple_half_product_half_sum_diff(neuron::Neuron *n); // add half of the input signals and multiply half input signals return diff

        void _simple_average(neuron::Neuron *n); // return the average of all input signals

        void _simple_add_res_square(neuron::Neuron *n); // add all input signals and return the square

        void _simple_product_res_square(neuron::Neuron *n); // multiply all input signals and return the square

        void _simple_square_sum(neuron::Neuron *n); // square all input signals and return the sum

        void _simple_square_product(neuron::Neuron *n); // square all input signals and return the product but will be subtracted by a value which is rand(0,1) * result
    };
};

#endif