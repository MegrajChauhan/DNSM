#ifndef _NEURON_
#define _NEURON_

#include <unordered_map>
#include <vector>
#include <string>
#include <thread>

namespace neuron
{
   class Neuron;

   typedef void (*activation_func_t)(Neuron *);

   class Path
   {
      Neuron *sender;
      Neuron *receiver;
      double _send_threshold; // must cross this threshold to send a signal
   };

   class Neuron
   {
      std::vector<Path> connections;
      double _conn_potential;
      double _conn_threshold;
      double _dest_potential;
      double _dest_threshold;
      activation_func_t _activation_func;
      std::vector<Neuron *> *_call_list;
      bool _io_neuron;
      std::vector<double> _inp_signals;

   public:
      Neuron() = default;

      void init(double cp, double ct, double dp, double dt, std::vector<Neuron*> cl, activation_func_t f, bool is_io);
   };
};

#endif