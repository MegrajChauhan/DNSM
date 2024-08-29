#ifndef _NEURON_
#define _NEURON_

#include <unordered_map>
#include <vector>
#include <string>
#include <thread>
#include <set>

namespace neuron
{
   class Neuron;

   typedef void (*activation_func_t)(Neuron *);
   typedef bool (*connect_func_t)(Neuron *);
   typedef bool (*destroy_func_t)(Neuron *);

   struct Path
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
      std::set<Neuron *> *_call_list;
      bool _io_neuron;
      std::vector<double> _inp_signals;
      double _res_signal; // the result of the activation function
      size_t ind = 0;

   public:
      Neuron() = default;

      void init(size_t i, double cp, double ct, double dp, double dt, std::set<Neuron *> *cl, activation_func_t f, bool is_io);

      void activate();

      void broadcast();

      void accept_val(double _sig);

      size_t get_ind();

      void connect(Neuron *receiver, double _th);

      void destroy_conn(size_t i);

      std::vector<double> *get_inp_signals();

      void result(double res);

      double get_res();
   };
};

#endif