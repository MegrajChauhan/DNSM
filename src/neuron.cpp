#include "neuron.hpp"

void DNSM::Neuron::init_neuron()
{
    Randomizer rand;

    sociability = rand.generate_double(0, 1);
    antisociability = 1.0 - sociability;

    openness = rand.generate_double(0, 1);
    shyness = 1.0 - openness;

    activity = rand.generate_double(0, 1);

    stimulation_threshold = rand.generate_double(0, 1);

    incoming_connections = 0;
    outgoing_connections = 0;
    killed_connections = 0;
    times_input_received = 0;
    identifying_mark = 0;

    _recently_path_changed = false;
    _connections_added = false;
    _connections_decreased = false;
}

void DNSM::Neuron::mark_neuron(size_t mark)
{
    identifying_mark = mark;
}

void DNSM::Neuron::activate(Path *incoming)
{
    __neuronstate_t new_state = _ACTIVATING;
    state = new_state;

    __path_field_t received_value = incoming->sent_signal;
    incoming->sent_signal = 0;

    current_output = activation_function({sociability, antisociability, openness, shyness, activity, stimulation_threshold, received_value});

    // We now have to do some in-between stuff
    // Should a new connection be built?
    // Should an old connection be destroyed?

    /**
     * The activation functions only provide a value using some mathmatical expression.
     * But we cannot afford to be abode by that as we have defined so many properties.
     * The result of the activation function will go through changes based on the properties of the
     * neuron.
     *
     * How are some actions decided?
     * On what basis should be decide that the neuron should build new connections or destroy old ones?
     * We can get as simple as using the incoming signal to using complex logic.
     * It depends.
     */

    current_output *= activity; // Higher activity results in stronger signals
    current_output = std::remainder(current_output, 1.0);

    

    new_state = _NEUTRAL;
defer:
    state = new_state;
}

void DNSM::Neuron::set_activation_func(__activationfn_t fn)
{
    activation_function = fn;
}

void DNSM::Neuron::obtain_neuron_lock()
{
    _change_lock.lock();
}

void DNSM::Neuron::release_neuron_lock()
{
    _change_lock.unlock();
}
