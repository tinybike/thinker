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

MTRand_open rand((unsigned)time(0));

NeuralNetwork::NeuralNetwork(const int n_inputs,
                             const int n_hidden,
                             const int n_outputs)
    : n_inputs(n_inputs + 1)
    , n_hidden(n_hidden)
    , n_outputs(n_outputs)
{
    // Initialize each neural layer
    input_layer.assign(n_inputs, 0.0);
    hidden_layer.assign(n_hidden, 0.0);
    output_layer.assign(n_outputs, 0.0);

    // Add a bias term to the input layer
    input_layer.push_back(1.0);
}

void NeuralNetwork::innervate()
{
    // Build weight matrices
    for (int i = 0; i < n_inputs; i++) {
        input_weights.push_back(nerve());
        for (int j = 0; j < n_hidden; j++) {
            input_weights[i].push_back(rzero(2.0*rand() - 1.0));
        }
    }
    for (int i = 0; i < n_hidden; i++) {
        output_weights.push_back(nerve());
        for (int j = 0; j < n_outputs; j++) {
            output_weights[i].push_back(rzero(2.0*rand() - 1.0));
        }
    }

    // Build feedback matrices
    for (int i = 0; i < n_inputs; i++) {
        hidden_feedback.push_back(nerve());
        for (int j = 0; j < n_hidden; j++) {
            hidden_feedback[i].push_back(0.0);
        }
    }
    for (int i = 0; i < n_hidden; i++) {
        output_feedback.push_back(nerve());
        for (int j = 0; j < n_outputs; j++) {
            output_feedback[i].push_back(0.0);
        }
    }
}

nerve NeuralNetwork::feedforward(const nerve& pattern)
{
    double weighted_sum;
    
    // Update input nodes (except bias term)
    for (int i = 0; i < n_inputs - 1; i++) {
        input_layer[i] = pattern[i];
    }

    // Update hidden nodes
    for (int i = 0; i < n_hidden; i++) {
        weighted_sum = 0.0;
        for (int j = 0; j < n_inputs; j++) {
            weighted_sum += input_layer[j] * input_weights[j][i];
        }
        hidden_layer[i] = logistic(weighted_sum);
    }

    // Update output nodes
    for (int i = 0; i < n_outputs; i++) {
        weighted_sum = 0.0;
        for (int j = 0; j < n_hidden; j++) {
            weighted_sum += hidden_layer[j] * output_weights[j][i];
        }
        output_layer[i] = logistic(weighted_sum);
    }

    return output_layer;
}

double NeuralNetwork::backpropagate(const nerve& target,
                                    const double learning_rate)
{
    double error;
    double sigmoid;
    double feedback_weight;
    double RMSE; // root mean squared error
    nerve output_feedback_updated;
    nerve hidden_feedback_updated;

    // Calculate updated output feedback vector
    for (int i = 0; i < n_outputs; i++) {
        error = rzero(target[i] - output_layer[i]);
        sigmoid = logistic(output_layer[i]);
        output_feedback_updated.push_back(rzero(error * sigmoid * (1.0 - sigmoid)));
    }

    // Calculate updated hidden feedback vector
    for (int i = 0; i < n_hidden; i++) {
        error = 0.0;
        for (int j = 0; j < n_outputs; j++) {
            error += rzero(output_feedback_updated[j] * output_weights[i][j]);
        }
        sigmoid = logistic(hidden_layer[i]);
        hidden_feedback_updated.push_back(rzero(error * sigmoid * (1.0 - sigmoid)));
    }

    // Update the hidden-to-output weights
    for (int i = 0; i < n_hidden; i++) {
        for (int j = 0; j < n_outputs; j++) {
            feedback_weight = rzero(output_feedback_updated[j] * hidden_layer[i]);
            output_weights[i][j] += rzero(learning_rate * feedback_weight);
            output_feedback[i][j] = feedback_weight;
        }
    }

    // Update the input-to-hidden weights
    for (int i = 0; i < n_inputs; i++) {
        for (int j = 0; j < n_hidden; j++) {
            feedback_weight = hidden_feedback_updated[j] * input_layer[i];
            input_weights[i][j] += rzero(learning_rate * feedback_weight);
            hidden_feedback[i][j] = feedback_weight;
        }
    }

    // Root mean squared error (RMSE) between desired and actual output
    RMSE = 0.0;
    for (int i = 0; i < n_outputs; i++) {
        RMSE += std::sqrt(std::pow(target[i] - output_layer[i], 2));
    }

    return RMSE / n_outputs;
}

inline double NeuralNetwork::logistic(const double x) const
{
    return rzero(1.0 / (1.0 + exp(-x)));
}

void NeuralNetwork::train(const synapse& input_grid,
                          const synapse& output_grid,
                          const int num_iterations,
                          const double learning_rate)
{
    double error;

    DEBUG("Training: %d iterations, %f learning rate\n",
          num_iterations, learning_rate);
    for (int i = 0; i < num_iterations; i++) {
        error = 0.0;
        for (unsigned j = 0; j < input_grid.size(); j++) {
            feedforward(input_grid[j]);
            error += backpropagate(output_grid[j], learning_rate);
        }
        if (i == 0) {
            DEBUG("Error [%d]: %f\n", i, error);
        }
    }
    DEBUG("Final error: %f\n", error);
    DEBUG("Training complete!\n");
}

void NeuralNetwork::test(const synapse& input_grid, const synapse& output_grid)
{
    nerve result;

    DEBUG("\nTesting [input --> output]:\n");
    for (unsigned i = 0; i < input_grid.size(); i++) {

        result = feedforward(input_grid[i]);
        
        for (unsigned j = 0; j < input_grid[i].size(); j++) {
            DEBUG("%f ", input_grid[i][j]);
        }
        DEBUG("--> ");
        for (unsigned j = 0; j < output_grid[i].size(); j++) {
            DEBUG("%f ", result[j]);
        }
        DEBUG("\n");
    }
    print_layers();
}

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

double rzero(const double x)
{
    if (x < EPSILON && x > -EPSILON) {
        return 0.0;
    }
    return x;
}

} // namespace

int main()
{
    const int INPUT_NODES = 7;
    const int HIDDEN_NODES = 4;
    const int OUTPUT_NODES = 7;

    // Create and initialize the neural network
    Thinker::NeuralNetwork neural_network(INPUT_NODES, HIDDEN_NODES, OUTPUT_NODES);
    neural_network.innervate();

    // Test drive the network
    Thinker::identity_matrix(neural_network, INPUT_NODES, OUTPUT_NODES);

    return 0;
}
