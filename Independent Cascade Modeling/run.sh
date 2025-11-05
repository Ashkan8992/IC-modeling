#!/bin/bash

# Compile all .cpp files # Link all object files into an executable
g++ main.cpp graph.cpp simulation.cpp -o ic_simulator -std=c++23
#g++ -fopenmp main.cpp graph.cpp simulation.cpp sim_parallel.cpp -o main -std=c++23

# Run the program with Format:
# Path to Input File (Graph Data) # Transmition Probability # Number of Repetitions
#./ic_simulator <graph_file> <output_file> <alpha> <num_threads> <num_simulations> <seed_mode> <num_seeds>
./ic_simulator "./DataSets/test.txt" "./test_output.txt" 0.2 0 10000 random 2 3

# Clean up object files
rm ic_simulator
