#ifndef __NEURALNET_H_INCLUDED__
#define __NEURALNET_H_INCLUDED__

#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include "mtrand.h"

namespace NeuralNet {

extern const int MAX_CYCLES;
extern const int NUMBER_OF_LAYERS;
extern const int NEURONS_PER_LAYER;
extern const double GOAL[4];

extern double INPUT_LIST[4][2];

class Neuron
{
private:
    std::vector<std::vector<double> > input;
    double * output, * grad, * weight;
    double lRate;
    int numInputs, numSets, layer;
public:
    Neuron() { }
    void initialize(int, int, double);
    void forward(int);
    void updateDeltas(int);
    void updateWeights(int);
    double sigmoid(double);
    int getNumInputs();
    int getNumSets();
    double getOutput(int);
    double getGrad(int);
    double getWeight(int);
};

bool complete();

} // namespace

extern std::vector<NeuralNet::Neuron> layers;
extern std::vector<std::vector<NeuralNet::Neuron> > network;

#endif
