#ifndef __THINKER_TEST_H_INCLUDED__
#define __THINKER_TEST_H_INCLUDED__

#include "thinker.h"

namespace Thinker {

class NeuralNetwork;

// Simple test problem: learn a 10x10 identity matrix
void identity_matrix(NeuralNetwork&, const int, const int);

} // namespace

#endif