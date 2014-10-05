#include "thinker.h"

namespace Thinker {

void NeuralNetwork::update_input_nodes(const nerve& pattern)
{
    // Update input nodes (except bias term)
    for (int i = 0; i < n_inputs - 1; i++) {
        input_layer[i] = pattern[i];
    }
}

void NeuralNetwork::update_hidden_nodes()
{
    double weighted_sum;
    for (int i = 0; i < n_hidden; i++) {
        weighted_sum = 0.0;
        for (int j = 0; j < n_inputs; j++) {
            weighted_sum += input_layer[j] * input_weights[j][i];
        }
        hidden_layer[i] = logistic(weighted_sum);
    }
}

void NeuralNetwork::update_output_nodes()
{
    double weighted_sum;
    for (int i = 0; i < n_outputs; i++) {
        weighted_sum = 0.0;
        for (int j = 0; j < n_hidden; j++) {
            weighted_sum += hidden_layer[j] * output_weights[j][i];
        }
        output_layer[i] = logistic(weighted_sum);
    }
}

} // Thinker
