## Thinker

Thinker is a [logistic-function neural network](http://en.wikipedia.org/wiki/Logistic_function#Neural_networks).

I originally built this to be used in conjunction with the [Ribosome Binding Site (RBS) Calculator](http://www.sciencedirect.com/science/article/pii/B9780123851208000024).  (A free-to-use web version of the RBS Calculator can be found [here](https://salis.psu.edu/software/).)  The goal of this project was to map ribosome binding site DNA sequences to their binding free energies.

To make a long story short, a neural network turned out not to be the best fit for this problem.  But, building Thinker was an enjoyable exercise, and it may be otherwise useful, so I'm making it available here.

### Usage

To install:

    $ make

To run:

    $ ./thinker -v

The `-v` flag causes `thinker` to output to the console.  If no flag is included, it will run silently.

To uninstall:

    $ make clean

By default, `thinker` is learning a simple XOR logic.  This is stored as `GOAL` in `thinker.cpp`.  You can edit this simply by changing the numbers in the `GOAL` variable, and re-compiling.  You can also set the number of layers, and number of neurons per layer, to be any size.
