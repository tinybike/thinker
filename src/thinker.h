#ifndef __THINKER_H_INCLUDED__
#define __THINKER_H_INCLUDED__

#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>
#include <limits>
#include "mtrand/mtrand.h"
#include "test.h"

#ifdef NDEBUG
#define DEBUG(format, args...) ((void)0)
#else
#define DEBUG printf
#endif

namespace Thinker {

extern const double EPSILON;

extern MTRand_open rand;

typedef std::vector<double> nerve;
typedef std::vector<std::vector<double> > synapse;

/** Three-layer feed-forward neural network with backpropagation */
class NeuralNetwork
{
private:
    int n_inputs;
    int n_hidden;
    int n_outputs;
    double learning_rate;
    nerve input_layer;
    nerve hidden_layer;
    nerve output_layer;
    synapse input_weights;      // forward: input -> hidden
    synapse output_weights;     // forward: hidden -> output
    synapse hidden_feedback;    // backward: hidden -> input
    synapse output_feedback;    // backward: output -> hidden
public:
    /** Create the neural net, and initialize its three layers. */
    NeuralNetwork(const int n_inputs,
                  const int n_hidden,
                  const int n_outputs,
                  const double learning_rate);
    /** Set up the weight and feedback matrices. */
    void innervate();
    /** Forward pass: neural net filters the input pattern. */
    nerve feedforward(const nerve& pattern);
    /** Reverse pass: neural net is trained on the target pattern. */
    double backpropagate(const nerve& target);
    /** Build inter-layer weight matrices. */
    void build_weight_matrix(synapse& weights,
                             const int n_from,
                             const int n_to);
    /** Build inter-layer feedback matrices. */
    void build_feedback_matrix(synapse& feedback,
                               const int n_from,
                               const int n_to);
    /** Update input nodes using the input pattern. */
    void update_input_nodes(const nerve& pattern);
    /** Propagate changes through the hidden and output nodes. */
    void update_nodes(const nerve& sender,
                      nerve& receiver,
                      const synapse& weights,
                      const int n_this,
                      const int n_prev);
    nerve update_output_feedback(const nerve& target);
    nerve update_hidden_feedback(const nerve& output_feedback_updated);
    void update_weights_feedback(const nerve& output_feedback_updated,
                                 const nerve& hidden_feedback_updated);
    /** Root mean squared error (RMSE) between desired and actual output. */
    double RMSE(const nerve& target) const;
    /** Logistic transfer function. */
    double logistic(const double) const;
    /** Train the neural net to map input_grid to output_grid. */
    void train(const synapse& input_grid, const synapse& output_grid,
               const int num_iterations);
    /** Post-training forward pass. */
    void verify(const synapse& input_grid, const synapse& output_grid);
    void print_layers() const;
    void print_weights() const;
    void print(const nerve&) const;
    void print(const synapse&) const;
};

/** Round negligibly small values to zero */
double rzero(const double);

} // namespace

#endif
