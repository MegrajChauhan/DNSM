#include <iostream>
#include "defin.hpp"
#include "neuron.hpp"
#include "defines.hpp"

struct DNSM
{
    std::vector<neuron::activation_func_t> func_list;
    std::set<neuron::Neuron *> call_list;
    std::vector<neuron::Neuron> neurons;
    std::vector<neuron::Neuron> input_neurons;
    std::vector<neuron::Neuron> output_neurons;
};

void populate_activate_functions(std::vector<neuron::activation_func_t> *);
void init_neuron(neuron::Neuron *, size_t, bool);
void init_io_neurons();
void init_hidden_neurons();
void randomize_connections();

static DNSM dnsm;

int main()
{
    populate_activate_functions(&dnsm.func_list);
    init_io_neurons();
    init_hidden_neurons();
    randomize_connections();
}

void populate_activate_functions(std::vector<neuron::activation_func_t> *func_list)
{
    func_list->push_back(&defin::activation::_simple_add);
    func_list->push_back(&defin::activation::_simple_add_res_square);
    func_list->push_back(&defin::activation::_simple_average);
    func_list->push_back(&defin::activation::_simple_half_product_half_sum_diff);
    func_list->push_back(&defin::activation::_simple_max);
    func_list->push_back(&defin::activation::_simple_max_min_diff);
    func_list->push_back(&defin::activation::_simple_product);
    func_list->push_back(&defin::activation::_simple_product_res_square);
    func_list->push_back(&defin::activation::_simple_product_sum_diff);
    func_list->push_back(&defin::activation::_simple_rand_times_max);
    func_list->push_back(&defin::activation::_simple_square_product);
    func_list->push_back(&defin::activation::_simple_square_sum);
}

void init_neuron(neuron::Neuron *n, size_t i, bool io)
{
    std::srand(time(NULL));
    n->init(i, ((double)rand() / (double)RAND_MAX) * (double)_FIELD_VAL_MAX_VAL, ((double)rand() / (double)RAND_MAX) * (double)_FIELD_VAL_MAX_VAL, ((double)rand() / (double)RAND_MAX) * (double)_FIELD_VAL_MAX_VAL, ((double)rand() / (double)RAND_MAX) * (double)_FIELD_VAL_MAX_VAL, &dnsm.call_list, dnsm.func_list[(size_t)(((double)rand() / (double)RAND_MAX) * (double)dnsm.func_list.size())], io);
}

void init_io_neurons()
{
    for (size_t i = 0; i < IO_NEURON_COUNT; i++)
    {
        neuron::Neuron n;
        init_neuron(&n, i, true);
        dnsm.input_neurons.push_back(n);
    }
    for (size_t i = 0; i < IO_NEURON_COUNT; i++)
    {
        neuron::Neuron n;
        init_neuron(&n, i, true);
        dnsm.output_neurons.push_back(n);
    }
}

void init_hidden_neurons()
{
    for (size_t i = 0; i < HIDDEN_NEURON_COUNT; i++)
    {
        neuron::Neuron n;
        init_neuron(&n, i, false);
        dnsm.neurons.push_back(n);
    }
}

void randomize_connections()
{
    // This randomizes in three-steps
    // First Input-Hidden
    // Second Hidden-Hidden
    // Third Hidden-Output
    for (size_t i = 0; i < INPUT_MAX_CONN; i++)
    {
        srand(time(NULL));
        int i1 = (rand() / RAND_MAX) * IO_NEURON_COUNT;
        int i2 = (rand() / RAND_MAX) * HIDDEN_NEURON_COUNT;
        dnsm.input_neurons[i1].connect(&dnsm.neurons[i2], ((double)rand() / (double)RAND_MAX) * (double)_PATH_THRESHOLD_MAX_);
    }
    for (size_t i = 0; i < HIDDEN_MAX_CONN; i++)
    {
        srand(time(NULL));
        int i1 = (rand() / RAND_MAX) * HIDDEN_NEURON_COUNT;
        int i2 = (rand() / RAND_MAX) * HIDDEN_NEURON_COUNT;
        dnsm.neurons[i1].connect(&dnsm.neurons[i2], ((double)rand() / (double)RAND_MAX) * (double)_PATH_THRESHOLD_MAX_);
    }
    for (size_t i = 0; i < OUTPUT_MAX_CONN; i++)
    {
        srand(time(NULL));
        int i1 = ((rand() / RAND_MAX) * IO_NEURON_COUNT);
        int i2 = (rand() / RAND_MAX) * HIDDEN_NEURON_COUNT;
        dnsm.output_neurons[i1].connect(&dnsm.neurons[i2], ((double)rand() / (double)RAND_MAX) * (double)_PATH_THRESHOLD_MAX_);
    }
}