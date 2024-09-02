#include "neuron.hpp"

void neuron::Neuron::init(size_t i, double cp, double ct, double dp, double dt, std::set<Neuron *> *cl, activation_func_t f, bool is_io)
{
    _conn_threshold = ct;
    _conn_potential = cp;
    _dest_potential = dp;
    _dest_threshold = dt;
    _activation_func = f;
    _call_list = cl;
    _io_neuron = is_io;
    ind = i;
}

void neuron::Neuron::activate()
{
    _activation_func(this); // this should handle all of it
    _inp_signals.clear();
}

void neuron::Neuron::broadcast()
{
    // Go through each path and broadcast the resulting signal
    // But only to those neurons who cross the threshold signal
    if (connections.empty())
        return;
    for (auto _p : connections)
    {
        if (_p._send_threshold <= _res_signal)
        {
            _p.receiver->accept_val(_res_signal);
            _call_list->insert(_p.receiver);
        }
    }
}

void neuron::Neuron::accept_val(double _sig)
{
    _inp_signals.push_back(_sig);
}

size_t neuron::Neuron::get_ind()
{
    return ind;
}

void neuron::Neuron::connect(Neuron *receiver, double _th)
{
    Path p;
    p.receiver = receiver;
    p.sender = this;
    p._send_threshold = _th;
    connections.push_back(p);
}

void neuron::Neuron::destroy_conn(size_t i)
{
    connections.erase(connections.begin() + i);
}

std::vector<double> *neuron::Neuron::get_inp_signals()
{
    return &_inp_signals;
}

void neuron::Neuron::result(double res)
{
    _res_signal = res;
}

double neuron::Neuron::get_res()
{
    return _res_signal;
}

void neuron::Neuron::provide_info(std::fstream *_stream)
{
    *_stream << "INDEX: " << ind << "\nCONN_POTEN: " << _conn_potential << "\nDEST_POTEN: " << _dest_potential << "\nCONN_THR: " << _conn_threshold << "\nDEST_THR: " << _dest_threshold;
    *_stream << "\n";
}

std::vector<neuron::Path> neuron::Neuron::get_connections()
{
    return connections;
}