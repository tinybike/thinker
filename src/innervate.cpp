#include "thinker.h"

namespace Thinker {

MTRand_open rand((unsigned)time(0));

void NeuralNetwork::build_weight_matrix(synapse& weights,
                                        const int n_from,
                                        const int n_to)
{
    for (int i = 0; i < n_from; i++) {
        weights.push_back(nerve());
        for (int j = 0; j < n_to; j++) {
            weights[i].push_back(rzero(2.0*rand() - 1.0));
        }
    }
}

void NeuralNetwork::build_feedback_matrix(synapse& feedback,
                                          const int n_from,
                                          const int n_to)
{
    for (int i = 0; i < n_from; i++) {
        feedback.push_back(nerve());
        for (int j = 0; j < n_to; j++) {
            feedback[i].push_back(0.0);
        }
    }
}

} // Thinker
