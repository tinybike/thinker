## Thinker

Thinker is a [logistic-function neural network](http://en.wikipedia.org/wiki/Logistic_function#Neural_networks).

I originally built this to be used in conjunction with the [Ribosome Binding Site Calculator](http://www.sciencedirect.com/science/article/pii/B9780123851208000024) (web app version [here](https://salis.psu.edu/software/).  Our aim was to map ribosome binding site DNA sequences to binding free energies (delta G).

To make a long story short, a neural network turned out not to be the best fit for this problem.  But, building Thinker was a fun exercise, so not a waste at all!

### Usage

To install:

    $ make

To run:

    $ ./neuralnet

To uninstall:

    $ make clean

By default, `neuralnet` is learning a simple XOR logic (`GOAL` in `neuralnet.cpp`).  You can also set the number of layers, and number of neurons per layer, to be any size.
