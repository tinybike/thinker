#include "thinker.h"

namespace Thinker {

void NeuralNetwork::update_input_nodes(const nerve& pattern)
{
    // Update input nodes (except bias term)
    for (int i = 0; i < n_inputs - 1; i++) {
        input_layer[i] = pattern[i];
    }
}

void NeuralNetwork::update_nodes(const nerve& sender,
                                 nerve& receiver,
                                 const synapse& weights,
                                 const int n_this,
                                 const int n_prev)
{
    // Update hidden and output nodes
    double weighted_sum;
    for (int i = 0; i < n_this; i++) {
        weighted_sum = 0.0;
        for (int j = 0; j < n_prev; j++) {
            weighted_sum += sender[j] * weights[j][i];
        }
        receiver[i] = logistic(weighted_sum);
    }
}

} // Thinker
