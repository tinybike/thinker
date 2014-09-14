/*********************************************************************
 * Thinker                                                           *
 *                                                                   *
 * Logistic-function neural network with backpropagation.            *
 *                                                                   *
 * (c) Jack Peterson, 9/9/2008                                       *
 *********************************************************************/

#include "thinker.h"
#include "test.h"

namespace Thinker {

NeuralNetwork::NeuralNetwork(const int n_inputs,
                             const int n_hidden,
                             const int n_outputs,
                             const double learning_rate)
    : n_inputs(n_inputs + 1)
    , n_hidden(n_hidden)
    , n_outputs(n_outputs)
    , learning_rate(learning_rate)
{
    input_layer.assign(n_inputs, 0.0);
    hidden_layer.assign(n_hidden, 0.0);
    output_layer.assign(n_outputs, 0.0);

    // Add a bias term to the input layer
    input_layer.push_back(1.0);
}

void NeuralNetwork::innervate()
{
    // Populate weight matrices with random values between 0 and 1
    build_weight_matrix(input_weights, n_inputs, n_hidden);
    build_weight_matrix(output_weights, n_hidden, n_outputs);

    // Populate feedback matrices with 0
    build_feedback_matrix(hidden_feedback, n_inputs, n_hidden);
    build_feedback_matrix(output_feedback, n_hidden, n_outputs);
}

nerve NeuralNetwork::feedforward(const nerve& pattern)
{
    // Update input nodes
    update_input_nodes(pattern);

    // Update hidden nodes
    update_nodes(input_layer, hidden_layer, input_weights, n_hidden, n_inputs);

    // Update output nodes
    update_nodes(hidden_layer, output_layer, output_weights, n_outputs, n_hidden);

    return output_layer;
}

double NeuralNetwork::backpropagate(const nerve& target)
{
    nerve output_feedback_updated = update_output_feedback(target);
    nerve hidden_feedback_updated = update_hidden_feedback(output_feedback_updated);    
    update_weights_feedback(output_feedback_updated,
                            hidden_feedback_updated);
    return RMSE(target);
}

double NeuralNetwork::logistic(const double x) const
{
    return 1.0 / (1.0 + std::exp(-x));
}

} // namespace

int main()
{
    const int INPUT_NODES = 7;
    const int HIDDEN_NODES = 4;
    const int OUTPUT_NODES = 7;
    const double LEARNING_RATE = 0.5;

    // Create and initialize the neural network
    Thinker::NeuralNetwork neural_network(INPUT_NODES,
                                          HIDDEN_NODES,
                                          OUTPUT_NODES,
                                          LEARNING_RATE);
    neural_network.innervate();

    // Test drive the network
    Thinker::identity_matrix(neural_network, INPUT_NODES, OUTPUT_NODES);

    return 0;
}
