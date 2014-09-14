#include "thinker.h"

namespace Thinker {

void NeuralNetwork::print_layers() const
{
    DEBUG("\nInputs [%d nodes]: ", n_inputs);
    print(input_layer);
    DEBUG("Hidden [%d nodes]: ", n_hidden);
    print(hidden_layer);
    DEBUG("Output [%d nodes]: ", n_outputs);
    print(output_layer);
    DEBUG("\n");
}

void NeuralNetwork::print_weights() const
{
    DEBUG("\nInput-to-hidden weights:");
    print(input_weights);
    DEBUG("\nHidden-to-output weights:");
    print(output_weights);
    DEBUG("\nInput-to-hidden deltas:");
    print(hidden_feedback);
    DEBUG("\nHidden-to-output deltas:");
    print(output_feedback);
}

void NeuralNetwork::print(const nerve& n) const
{
    for (unsigned i = 0; i < n.size(); i++) {
        DEBUG("%f ", n[i]);
    }
    DEBUG("\n");
}

void NeuralNetwork::print(const synapse& s) const
{
    for (unsigned i = 0; i < s.size(); i++) {
        for (unsigned j = 0; j < s[i].size(); j++) {
            DEBUG("%f ", s[i][j]);
        }
        DEBUG("\n");
    }
    DEBUG("\n");
}

} // Thinker
