#include "thinker.h"

namespace Thinker {

void NeuralNetwork::train(const synapse& input_grid,
                          const synapse& output_grid,
                          const int num_iterations)
{
    double error;

    DEBUG("Training: %d iterations, %f learning rate\n",
          num_iterations, learning_rate);
    for (int i = 0; i < num_iterations; i++) {
        error = 0.0;
        for (unsigned j = 0; j < input_grid.size(); j++) {
            feedforward(input_grid[j]);
            error += backpropagate(output_grid[j]);
        }
        if (i == 0) {
            DEBUG("Error [%d]: %f\n", i, error);
        }
    }
    DEBUG("Final error: %f\n", error);
    DEBUG("Training complete!\n");
}

void NeuralNetwork::verify(const synapse& input_grid, const synapse& output_grid)
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

} // Thinker
