#ifndef __THINKER_H_INCLUDED__
#define __THINKER_H_INCLUDED__

#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>
#include <limits>
#include "mtrand.h"
#include "test.h"

#ifdef NDEBUG
#define DEBUG(format, args...) ((void)0)
#else
#define DEBUG printf
#endif

namespace Thinker {

static const double EPSILON = std::numeric_limits<double>::epsilon();

typedef std::vector<double> nerve;
typedef std::vector<std::vector<double> > synapse;

/** Three-layer feed-forward neural network with backpropagation */
class NeuralNetwork
{
private:
    int n_inputs;
    int n_hidden;
    int n_outputs;
    nerve input_layer;
    nerve hidden_layer;
    nerve output_layer;
    synapse input_weights;      // forward: input -> hidden
    synapse output_weights;     // forward: hidden -> output
    synapse hidden_feedback;    // backward: hidden -> input
    synapse output_feedback;    // backward: output -> hidden
public:
    /** Create the neural net, and initialize its three layers. */
    NeuralNetwork(const int n_inputs, const int n_hidden, const int n_outputs);
    /** Set up the interlayer weight matrices. */
    void innervate();
    /** Forward pass: neural net filters the input pattern. */
    nerve feedforward(const nerve& pattern);
    /** Reverse pass: neural net is trained on the target pattern. */
    double backpropagate(const nerve& target, const double learning_rate);
    /** Logistic transfer function. */
    inline double logistic(const double) const;
    /** Train the neural net to map input_grid to output_grid. */
    void train(const synapse& input_grid, const synapse& output_grid,
               const int num_iterations, const double learning_rate);
    /** Post-training forward pass. */
    void test(const synapse& input_grid, const synapse& output_grid);
    void print_layers() const;
    void print_weights() const;
    void print(const nerve&) const;
    void print(const synapse&) const;
};

/** Round negligibly small values to zero */
double rzero(const double);

} // namespace

#endif
