//  simulation.hpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/16/25.

#ifndef simulation_hpp
#define simulation_hpp

#include <math.h>
#include <queue>
#include <random>
#include <thread>

#include "graph.hpp"

class Sim {
    Graph& net;
    size_t reps;
    int src_count;
    double transmit_prob;
    std::vector<int> sources;
    
public:
    std::vector<double> access_probs;
    
    Sim(Graph&, size_t, double, int, std::string);
    
    void generate_sources(std::string); // Options: Random, Max-Degree TODO: Central, etc.
    void runSim(size_t, std::vector<int>&); // Independent Cascade Model
    void runParallelSim(int); // Parallel of the above
    void printAccessProbs(std::string);
};

#endif /* simulation_hpp */
