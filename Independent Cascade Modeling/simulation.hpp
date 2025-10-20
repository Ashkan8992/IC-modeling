//  simulation.hpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/16/25.

#ifndef simulation_hpp
#define simulation_hpp

#include <math.h>
#include <queue>
#include <random>

#include "graph.hpp"

class Sim {
    Graph& net;
    unsigned int reps;
    double transmit_prob;
    std::vector<double> access_probs;
    std::vector<int> sources;
    
public:
    Sim(Graph&, unsigned int, double);
    
    void generate_sources(); // TODO: Multiple options
    void runMonteCarloSim(); // Independent Cascade Model
    void printAccessProbs();
};

#endif /* simulation_hpp */
