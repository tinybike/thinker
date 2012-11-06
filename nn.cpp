/*********************************************************************
 * nn.cpp                                                            *
 * Logistic function neural network (compile with Mersenne-Twister   *
 * random number generator, mtrand.cpp)                              *
 * (c) Jack Peterson, 9/9/2008                                       *
 *********************************************************************/

#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include "mtrand.h"

using namespace std;

const int MAX_CYCLES = 100000;
const int NUMBER_OF_LAYERS = 3;
const int NEURONS_PER_LAYER = 4;
const double GOAL[4] = {0.0, 1.0, 1.0, 0.0};
double INPUT_LIST[4][2] = {{0.0, 0.0},
                           {1.0, 0.0},
                           {0.0, 1.0},
                           {1.0, 1.0}};

// Seed random number generator with system time
MTRand_open mt((unsigned)time(0));

class Neuron
{
private:
 vector<vector<double> > input;
 double * output, * grad, * weight;
 double lRate;
 int numInputs, numSets, layer;
public:
 Neuron() { }
 // Empty constructor: use initializer for neuron construction
 void initialize(int L, int N, double R)
 {
  layer = L;
  numInputs = N + 1;
  numSets = 4;
  lRate = R;
  // Initialize a numSets x numInputs vector of zeros for input
  vector<double> numPerSet(numInputs);
  output = new double[numSets];
  grad = new double[numSets];
  for(int i = 0; i < numSets; i++)
  {
   output[i] = 0.0;
   grad[i] = 0.0;
   input.push_back(numPerSet);
   // Insert static threshold (bias) of -1.0
   input[i][numInputs - 1] = -1.0;
  }
  // Initialize weight to random values on (-1, 1)
  weight = new double[numInputs];
  cout << "++ Layer " << layer << " neuron: [ ";
  for(int i = 0; i < numInputs; i++)
  {
   weight[i] = (2 * (mt() - 0.5));
   cout << weight[i] << " ";
  }
  cout << "] ++\n";
 }
 void forward(int);
 void updateDeltas(int);
 void updateWeights(int);
 double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }
 // Functions to access and return member data
 int getNumInputs() { return numInputs; }
 int getNumSets() { return numSets; }
 double getOutput(int i) { return output[i]; }
 double getGrad(int i) { return grad[i]; }
 double getWeight(int i) { return weight[i]; }
};

///////////////// Network declaration and sizing /////////////////

vector<Neuron> layers(NUMBER_OF_LAYERS);
vector<vector<Neuron> > network(NEURONS_PER_LAYER + 1, layers);

//////////////////////////////////////////////////////////////////

void Neuron::forward(int inputSet)
{
 switch(layer)
 {
  case 0:
  {
   double (* pTemp)[2];
   pTemp = INPUT_LIST;
   for(int i = 0; i < numInputs - 1; i++)
    input[inputSet][i] = pTemp[inputSet][i];
   break;
  }
  default:
  {
   // Use the previous layer's output as this layer's input
   for(int i = 0; i < numInputs - 1; i++)
    input[inputSet][i] = network[i][layer - 1].getOutput(inputSet);
   break;
  }
 }
 // Calculate the neuron's output from the weighted inputs
 double product = 0.0;
 for(int i = 0; i < numInputs; i++)
  product += weight[i] * input[inputSet][i];
 output[inputSet] = sigmoid(product);
}

void Neuron::updateDeltas(int inputSet)
{
 double error;
 switch(layer)
 {
  case NUMBER_OF_LAYERS - 1:
  {
   // Calculate how far off the output is from the goal, and
   // adjust the hidden-to-output weights
   error = GOAL[inputSet] - output[inputSet];
   grad[inputSet] = error * output[inputSet] * (1 - output[inputSet]);
   break;
  }
  default:
  {
   // Backpropagate the error and adjust the previous-to-current
   // layer weights based on the gradients of the next layer
   error = 0.0;
   for(int i = 0; i < network[0][layer + 1].getNumInputs(); i++)
    error += network[i][layer + 1].getWeight(i) * network[i][layer + 1].getGrad(inputSet);
   grad[inputSet] = error * output[inputSet] * (1 - output[inputSet]);
   break;
  }
 }
}

void Neuron::updateWeights(int inputSet)
{
 for(int i = 0; i < numInputs; i++)
  weight[i] += lRate * grad[inputSet] * input[inputSet][i];
}

bool complete()
{
 // Check if the network output is sufficiently close to the goal
 for(int i = 0; i < 4; i++)
 {
  if(fabs(GOAL[i] - network[0][NUMBER_OF_LAYERS - 1].getOutput(i)) > 0.01) 
   return false;
 }
 return true;
}

int main()
{
 bool result = false;
 // Initialize the network
 for(int i = 0; i < NUMBER_OF_LAYERS; i++)
 {
  for(int j = 0; j <= NEURONS_PER_LAYER; j++)
   network[j][i].initialize(i, NEURONS_PER_LAYER, 0.25);
 }
 cout << "\n";
 // Train the network
 cout << "Goal: [ ";
 for(int j = 0; j < 4; j++)
  cout << GOAL[j] << " ";
 cout << "]\nLayer " << NUMBER_OF_LAYERS - 1 << " output:\n";
 for(int i = 0; i < MAX_CYCLES; i++)
 {
  // Forward pass: layer 0 -> (NUMBER_OF_LAYERS - 1)
  for(int j = 0; j < 4; j++)
  {
   for(int l = 0; l < NUMBER_OF_LAYERS; l++)
   {
    for(int m = 0; m <= NEURONS_PER_LAYER; m++)
     network[m][l].forward(j);
   }
  }
  // Reverse pass: layer (NUMBER_OF_LAYERS - 1) -> 0
  for(int j = 0; j < 4; j++)
  {
   for(int l = NUMBER_OF_LAYERS - 1; l >= 0; l--)
   {
    for(int m = NEURONS_PER_LAYER; m >= 0; m--)
     network[m][l].updateDeltas(j);
   }
  }
  for(int j = 0; j < 4; j++)
  {
   for(int l = NUMBER_OF_LAYERS - 1; l >= 0; l--)
   {
    for(int m = NEURONS_PER_LAYER; m >= 0; m--)
     network[m][l].updateWeights(j);
   }
  }
  // Display the network's output, and check if it is complete
  cout << "[ ";
  for(int j = 0; j < 4; j++)
   cout << network[0][NUMBER_OF_LAYERS - 1].getOutput(j) << " ";
  result = complete();
  cout << "]\n";
  if(result)
  {
   cout << "\n**** Training successful after " << i << " cycles! ****\n";
   i = MAX_CYCLES;
  }
 }
 if(!result)
  cout << "\n**** Training failed. ****\n";
 cout << "Goal: [ ";
 for(int j = 0; j < 4; j++)
  cout << GOAL[j] << " ";
 cout << "]\n";
 cout << "Final network weights:\n";
 for(int j = 0; j < NUMBER_OF_LAYERS; j++)
 {
  for(int k = 0; k < NEURONS_PER_LAYER; k++)
  {
   cout << "Layer " << j << ": [ ";
   for(int l = 0; l < network[k][j].getNumInputs(); l++)
    cout << network[k][j].getWeight(l) << " ";
   cout << "]\n";
  }
 }
 cout << "\n";
 return 0;
}