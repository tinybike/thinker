## Thinker

[![Build Status](https://travis-ci.org/tensorjack/thinker.svg?branch=master)](https://travis-ci.org/tensorjack/thinker)

Thinker is an artificial neural network with a [logistic transfer function](http://en.wikipedia.org/wiki/Logistic_function#Neural_networks), which can be trained using [backpropagation](http://en.wikipedia.org/wiki/Backpropagation).

I originally built Thinker to be used in conjunction with the [Ribosome Binding Site (RBS) Calculator](http://www.sciencedirect.com/science/article/pii/B9780123851208000024).  A free-to-use web version of the RBS Calculator can be found on the Salis lab's [website](https://salis.psu.edu/software/).  The goal of this project was to map the DNA sequences of ribosome binding sites to their binding free energies.

To make a long story short, a neural network turned out not to be the best fit for this problem.  However, I liked the way this program turned out, so I'm making it available here.  Hopefully someone will find it useful!

### Usage

To install:

    $ make

To run:

    $ ./thinker

To suppress logging, compile with the `-DNDEBUG` flag.

To uninstall:

    $ make clean

The example training/testing problem included with Thinker has it learn a simple identity matrix.  You can alter the size of this problem by editing the number of input layer (`INPUT_NODES`) and output layer (`OUTPUT_NODES`) neurons.  The size of the hidden layer (`HIDDEN_NODES`) can be adjusted either for greater generalizability (lower number) or more exact fit (higher number).
