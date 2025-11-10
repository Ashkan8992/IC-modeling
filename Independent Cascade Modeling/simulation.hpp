//  simulation.hpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/16/25.

#ifndef simulation_hpp
#define simulation_hpp

#include <math.h>
#include <queue>
#include <random>
#include <set>
#include <thread>

#include "graph.hpp"

class Sim {
    Graph& net;
    size_t reps;
    int src_count;
    double transmit_prob;
    std::set<int> sources;
    int num_threads;
    
public:
    std::vector<double> access_probs;
    
    Sim(Graph&, size_t, double, int, std::string, int);
    
    int get_src_count();
    Graph& get_graph();
    
    void generate_sources(std::string); // Options: Random, Max-Degree TODO: Central, etc.
    void add_src(int);
    void remove_src(int);
    bool contain_src(int);
    
    double get_average(); // Returns the average access of all nodes
    double get_min(); // Returns the min access among all nodes
    
    void runSim(size_t, std::vector<int>&); // Independent Cascade Model
    void runParallelSim(); // Parallel of the above
    void printAccessProbs(std::string);
};

#endif /* simulation_hpp */
