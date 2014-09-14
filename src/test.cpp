#include "thinker.h"
#include "test.h"

#define THINKER_MAX_CYCLES 10000

namespace Thinker {

void identity_matrix(NeuralNetwork& neural_network,
                     const int n_inputs,
                     const int n_outputs)
{
    double node;
    synapse input_grid;
    synapse output_grid;

    // Set up the inputs and outputs
    for (int i = 0; i < n_inputs; i++) {

        input_grid.push_back(nerve());
        output_grid.push_back(nerve());

        for (int j = 0; j < n_outputs; j++) {
            node = (j == i) ? 1.0 : 0.0;
            input_grid[i].push_back(node);
            output_grid[i].push_back(node);
        }
    }

    // Set up the network structure, train it, and show test results
    neural_network.train(input_grid, output_grid, THINKER_MAX_CYCLES);
    neural_network.verify(input_grid, output_grid);
}

} // namespace
