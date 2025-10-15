#!/bin/bash

# Compile all .cpp files # Link all object files into an executable
g++ main.cpp graph.cpp -o main -std=c++23

# Run the program with Format:
# Path to Input File (Graph Data) # Transmition Probability # Number of Repetitions
./main "./DataSets/test.txt" 0.1 10000

# Clean up object files
rm main
