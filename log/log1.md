# Rough Idea: Implementation
The initial idea for the implemented model has proven to be extremely problematic. Each problem encountered spawns multiple new issues. The solutions, regardless of choice, invariably add further complications. As a result, it’s clear that the model is flawed and requires improvements—both logically and pragmatically.

The current model primarily suffers from:
1. Excessive computation costs.
2. High memory consumption.
3. The excessive amount of metadata required to store the state at any given time.
4. Logical flaws and gaps.
5. Overly complex problems followed by exceedingly complicated solutions.
6. Difficulty in tracking data flow.
7. Lack of predefined methods and solutions to address these issues.

These issues may also be due to my own shortcomings—perhaps insufficient research and exploration on my part—but one thing is clear: the number of problems outweighs the model’s applicability.

# Some Terms:
1. **Signal**: The numerical value that a neuron transmits to its neighbors.
2. **Cycle**: One cycle signifies the movement of a signal from Neuron 'X' to Neuron 'X+1'.
3. **Path**: A path is a pathway that connects two neurons, allowing the movement of signals.

# Some problems encountered
The issues are already explained in **challenges.md**, but here are additional details:
1. **No Progress Tracking:** The model lacks a way to convey its information and structure, making it impossible for us to track any part of the network. Reasons include **problem 2**, **problem 3**, **problem 4**, **problem 5**, and others, which all prevent effective monitoring.
2. **Loops:** Due to random, unpredictable connections between neurons, it's impossible to know if a connection forms a loop. When these loops occur, signals circulate endlessly, never reaching the output neurons. Because of the model’s dynamic nature, it’s infeasible to determine if a connection is part of a loop, especially in networks with many neurons.
3. **Dead Paths:** These are paths that never activate, regardless of input. Some reasons are clear, such as a neuron closing the input connection most likely to activate it or having an activation value that's too high or too low. The latter may stem from logical errors in the implementation rather than the neuron’s behavior.
4. **Variable Path Lengths:** This problem is directly related to problem 5; if resolved, it would also solve problem 5. Ideally, a neuron should receive inputs from all its connections. However, in a dynamic network, neurons may have multiple input connections with varying path lengths—for example, one input might take 5 paths to arrive while another takes 11. This makes it challenging to ensure synchronized arrival.
5. **Unknown Data Arrival Time:** Since we need to wait for all input data to arrive before proceeding, we would ideally track the number of cycles needed for all inputs. However, due to problem 4, this is impractical.

Some more issues include:
1. **Value mess, Interpretations and Intelligent choice of values:** The network's design allows a creator to add any kind of value, give the value their own interpretation and incorporate that value into representing the state of a neuron in some way or use it in some way to create the signals. It is necessary to carefully choose these values. The already
defined values are already too many and so care must be taken.
2. **Connections:** The problems related to the paths isn't limited to what were mentioned above. One neuron may form a path: to itself, to any neuron that gave it it's input, basically any neuron in the network. This alone adds many problems. A need to introduce a type paths and connections arises as well which, again, adds more problmes.
3. **Isolated or Lone Groups:** These groups consists of neurons that have separated themselves from the main network and are taking no input connections or sending any outputs.

# Changes to the Rough Idea
The entire network will work differently now. This will solve many of the problems but at the cost of other things. Firstly, the neurons will no longer need to wait for all inputs.
The true purpose of this network is to model a biological neural network. A biological neuron immediately transmits any input it receives via any path that is suitable i.e a path which
fulfills the required signal strength. This model will do the same. Doing this alone will solve many of the problems but adds a new complexity to the implementation. We will need to
run one path per thread. For eg: Say we have three input neurons N1, N2 and N3. After receiving inputs, we will have to start three threads where each input will traverse the network.
Say N3 goes to N5 which transmits to N7 and N9. With two neurons, we will need two new threads tracking those new paths hence the complexity. The solution is to use thread pools where the
currently active neuron will queue the next neuron to be activated and so on till we reach the output.
