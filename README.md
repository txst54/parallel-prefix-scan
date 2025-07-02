# Parallel Prefix Scan

Some experiments in work efficient algorithms.
I have implemented a sequential and parallel Blelloch scan via `seq_tree` and `p_tree` respectively. 
I've also implemented a more cache-coherent blocked version via `p_block`. 
The algorithms work on arrays of integers, and arrays of floating point vectors. 

## Run
To compile, `mkdir build & cd build & cmake .. & make` 

To generate tests, run `python gentest.py`. You can modify the hyperparameters in the test generation suite to generate larger or smaller datasets. 

To run, run `build/parallel_prefix_sums` 

To plot performance run `python plot.py`