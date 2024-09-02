#ifndef _DEFINES_
#define _DEFINES_

#define IO_NEURON_COUNT 4 // 4 each- Input and Output
#define HIDDEN_NEURON_COUNT 10

#define _FIELD_VAL_MAX_VAL 55.65 // for now any field may have a value of 100 maximum

/// NOTE: Notice how the number of max conditions exceeds the number of neurons
/// NOTE: The below only tells us about how many random connections are made at the start
#define INPUT_MAX_CONN 8   // The maximum number of Input-Hidden connections
#define OUTPUT_MAX_CONN 8  // The maximum number of Output-Hidden connections
#define HIDDEN_MAX_CONN 15 // The maximum number of Hidden-Hidden connections

#define _PATH_THRESHOLD_MAX_ 4.33

#endif