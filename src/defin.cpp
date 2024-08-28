#include "defin.hpp"

void defin::activation::_simple_add(neuron::Neuron *n)
{
    double result = 0;
    std::vector<double> *signals = n->get_inp_signals();
    for (const auto _s : *signals)
        result += _s;
    n->result(result);
    signals->erase(signals->begin(), signals->end());
}

void defin::activation::_simple_product(neuron::Neuron *n)
{
    double result = 0;
    std::vector<double> *signals = n->get_inp_signals();
    for (const auto _s : *signals)
        result *= _s;
    n->result(result);
    signals->erase(signals->begin(), signals->end());
}

void defin::activation::_simple_max(neuron::Neuron *n)
{
    std::vector<double> *signals = n->get_inp_signals();
    double result = *std::max_element(signals->begin(), signals->end());
    n->result(result);
    signals->erase(signals->begin(), signals->end());
}

void defin::activation::_simple_max_min_diff(neuron::Neuron *n)
{
    std::vector<double> *signals = n->get_inp_signals();
    double result = *std::max_element(signals->begin(), signals->end()) - *std::min_element(signals->begin(), signals->end());
    n->result(result);
    signals->erase(signals->begin(), signals->end());
}

void defin::activation::_simple_rand_times_max(neuron::Neuron *n)
{
    std::srand(std::clock()); // not the best of options
    std::vector<double> *signals = n->get_inp_signals();
    double result = *std::max_element(signals->begin(), signals->end()) * (std::rand() / RAND_MAX);
    n->result(result);
    signals->erase(signals->begin(), signals->end());
}

void defin::activation::_simple_product_sum_diff(neuron::Neuron *n)
{
    double result = 0;
    std::vector<double> *signals = n->get_inp_signals();
    for (const auto _s : *signals)
        result += _s;
    _simple_product(n);
    result = n->get_res() - result;
    n->result(result);
}

void defin::activation::_simple_half_product_half_sum_diff(neuron::Neuron *n)
{
    double result = 0;
    std::vector<double> *signals = n->get_inp_signals();

    size_t len = signals->size();
    // len cannot be guranteed to be divisible by 2
    // Thus if any elements are left then they will be added instead
    // of being multiplied
    size_t mul_len = len / 2;
    size_t add_len = len - mul_len;

    double _sum_res = 0, _mul_res = 0;

    for (size_t i = 0; i < add_len; i++)
        _sum_res += (*signals)[i];
    for (size_t i = add_len; i < mul_len; i++)
        _mul_res *= (*signals)[i];

    result = _mul_res - _sum_res;
    n->result(result);
    signals->erase(signals->begin(), signals->end());
}

void defin::activation::_simple_average(neuron::Neuron *n)
{
    double res = 0;
    size_t len = n->get_inp_signals()->size();
    _simple_add(n);
    res = n->get_res() / len;
    n->result(res);
}

void defin::activation::_simple_add_res_square(neuron::Neuron *n)
{
    _simple_add(n);
    n->result(std::pow(n->get_res(), 2));
}

void defin::activation::_simple_product_res_square(neuron::Neuron *n)
{
    _simple_product(n);
    n->result(std::pow(n->get_res(), 2));
}

void defin::activation::_simple_square_sum(neuron::Neuron *n)
{
    double result = 0;
    std::vector<double> *signals = n->get_inp_signals();
    for (const auto _s : *signals)
        result += std::pow(_s, 2);
    n->result(result);
    signals->erase(signals->begin(), signals->end());
}

void defin::activation::_simple_square_product(neuron::Neuron *n)
{
    double result = 0;
    std::vector<double> *signals = n->get_inp_signals();
    for (const auto _s : *signals)
        result *= std::pow(_s, 2);
    n->result(result - ((std::rand() / RAND_MAX) * result));
    signals->erase(signals->begin(), signals->end());
}