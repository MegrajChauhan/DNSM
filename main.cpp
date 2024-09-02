#include <iostream>
#include "defin.hpp"
#include "neuron.hpp"
#include "defines.hpp"
#include <random>
#include <array>
#include <fstream>

#define _FNAME_ "text.txt"

struct DNSM
{
    std::vector<neuron::activation_func_t> func_list;
    std::set<neuron::Neuron *> call_list;
    std::vector<neuron::Neuron> neurons;
    std::vector<neuron::Neuron> input_neurons;
    std::vector<neuron::Neuron> output_neurons;
    std::vector<std::array<uint8_t, IO_NEURON_COUNT>> input;
};

void populate_activate_functions(std::vector<neuron::activation_func_t> *);
void init_neuron(neuron::Neuron *, size_t, bool);
void init_io_neurons();
void init_hidden_neurons();
void randomize_connections();
void run_network();
void textualize_network();

static DNSM dnsm;

int main()
{
    populate_activate_functions(&dnsm.func_list);
    init_io_neurons();
    init_hidden_neurons();
    randomize_connections();
    // textualize_network();
    std::array<uint8_t, IO_NEURON_COUNT> i = {'1', '+', '2', '3'};
    dnsm.input.push_back(i);
    i = {'1', '+', '1', '2'};
    dnsm.input.push_back(i);
    run_network();
    // we will define how we get our inputs later on
    // for now we just have to setup something
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

void init_neuron(neuron::Neuron *n, size_t i, bool io)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, _FIELD_VAL_MAX_VAL);
    std::uniform_int_distribution<> func_dis(0, dnsm.func_list.size() - 1);

    n->init(i, dis(gen), dis(gen), dis(gen), dis(gen), &dnsm.call_list, dnsm.func_list[func_dis(gen)], io);
}

void randomize_connections()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> threshold_dis(0.0, _PATH_THRESHOLD_MAX_);
    std::uniform_int_distribution<> io_dis(0, IO_NEURON_COUNT - 1);
    std::uniform_int_distribution<> hidden_dis(0, HIDDEN_NEURON_COUNT - 1);

    // Randomize Input-Hidden connections
    for (size_t i = 0; i < INPUT_MAX_CONN; i++)
    {
        int i1 = io_dis(gen);
        int i2 = hidden_dis(gen);
        dnsm.input_neurons[i1].connect(&dnsm.neurons[i2], threshold_dis(gen));
    }

    // Randomize Hidden-Hidden connections
    for (size_t i = 0; i < HIDDEN_MAX_CONN; i++)
    {
        int i1 = hidden_dis(gen);
        int i2 = hidden_dis(gen);
        dnsm.neurons[i1].connect(&dnsm.neurons[i2], threshold_dis(gen));
    }

    // Randomize Hidden-Output connections
    for (size_t i = 0; i < OUTPUT_MAX_CONN; i++)
    {
        int i1 = io_dis(gen);
        int i2 = hidden_dis(gen);
        dnsm.neurons[i1].connect(&dnsm.output_neurons[i2], threshold_dis(gen));
    }
}

void run_network()
{
    for (auto _in : dnsm.input)
    {
        size_t i = 0;
        for (auto n : dnsm.input_neurons)
        {
            n.accept_val((double)_in[i]);
            n.activate();
            n.broadcast();
            i++;
        }
        while (!dnsm.call_list.empty())
        {
            auto temp = dnsm.call_list;
            dnsm.call_list.clear();
            for (auto _neuron : temp)
            {
                _neuron->activate();
                _neuron->broadcast();
                // we aren't worried about creating new connections or destroying old connections yet
            }
        }
        for (auto _on : dnsm.output_neurons)
        {
            // _on.activate();
            std::cout << "OUTPUT: [" << _on.get_ind() << "]: " << _on.get_res() << "\n";
        }
    }
}

void textualize_network()
{
    std::fstream f(_FNAME_, std::ios::out);
    f << "NEURON INFO:\n";
    // Input neurons
    f << "\nINPUT NEURONS:\n";
    for (auto n : dnsm.input_neurons)
        n.provide_info(&f);
    // output neurons
    f << "\nOUTPUT NEURONS:\n";
    for (auto n : dnsm.output_neurons)
        n.provide_info(&f);
    // hidden neurons
    f << "\nHIDDEN NEURONS:\n";
    for (auto n : dnsm.neurons)
        n.provide_info(&f);
    f << "\nALL CONNECTIONS:\n";
    // trace connections
    f << "\nINPUT NEURONS:\n";
    for (auto n : dnsm.input_neurons)
    {
        auto conn = n.get_connections();
        if (conn.empty())
            continue;
        f << "IND: " << n.get_ind() << "\n";
        for (auto p : conn)
            f << "\t<" << p._send_threshold << ">: " << "IND: " << p.receiver->get_ind() << "\n";
    }
    f << "\nHIDDEN NEURONS:\n";
    for (auto n : dnsm.neurons)
    {
        auto conn = n.get_connections();
        if (conn.empty())
            continue;
        f << "IND: " << n.get_ind() << "\n";
        for (auto p : conn)
            f << "\t<" << p._send_threshold << ">: " << "IND: " << p.receiver->get_ind() << "\n";
    }
    f << "\nOUTPUT NEURONS:\n";
    for (auto n : dnsm.output_neurons)
    {
        auto conn = n.get_connections();
        if (conn.empty())
            continue;
        f << "IND: " << n.get_ind() << "\n";
        for (auto p : conn)
            f << "\t<" << p._send_threshold << ">: " << "IND: " << p.receiver->get_ind() << "\n";
    }
    f.close();
}