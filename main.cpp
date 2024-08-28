#include <iostream>
#include "defin.hpp"
#include "neuron.hpp"

void populate_activate_functions(std::vector<neuron::activation_func_t> *);

int main()
{
    std::vector<neuron::activation_func_t> func_list;
    std::vector<neuron::Neuron> neurons;
    std::vector<neuron::Neuron> _io_neurons;
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