#include "thinker.h"

namespace Thinker {

const double EPSILON = std::numeric_limits<double>::epsilon();

nerve NeuralNetwork::update_output_feedback(const nerve& target)
{
    double error;
    double sigmoid;
    nerve output_feedback_updated;

    // Calculate updated output feedback vector
    for (int i = 0; i < n_outputs; i++) {
        error = rzero(target[i] - output_layer[i]);
        sigmoid = logistic(output_layer[i]);
        output_feedback_updated.push_back(rzero(error * sigmoid * (1.0 - sigmoid)));
    }
    return output_feedback_updated;
}

nerve NeuralNetwork::update_hidden_feedback(const nerve& output_feedback_updated)
{
    double error;
    double sigmoid;
    nerve hidden_feedback_updated;

    // Calculate updated hidden feedback vector
    for (int i = 0; i < n_hidden; i++) {
        error = 0.0;
        for (int j = 0; j < n_outputs; j++) {
            error += rzero(output_feedback_updated[j] * output_weights[i][j]);
        }
        sigmoid = logistic(hidden_layer[i]);
        hidden_feedback_updated.push_back(rzero(error * sigmoid * (1.0 - sigmoid)));
    }
    return hidden_feedback_updated;
}

void NeuralNetwork::update_weights_feedback(const nerve& output_feedback_updated,
                                            const nerve& hidden_feedback_updated)
{
    double feedback_weight;

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
}

double NeuralNetwork::RMSE(const nerve& target) const
{
    // Root mean squared error (RMSE) between desired and actual output
    double error = 0.0;
    
    for (int i = 0; i < n_outputs; i++) {
        error += std::sqrt(std::pow(target[i] - output_layer[i], 2));
    }
    return error / n_outputs;   
}

double rzero(const double x)
{
    if (x < EPSILON && x > -EPSILON) {
        return 0.0;
    }
    return x;
}

} // Thinker
