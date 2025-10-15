//  graph.hpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/15/25.

#ifndef graph_hpp
#define graph_hpp

#include <fstream>
#include <iostream>
#include <random>
#include <stdio.h>
#include <string>
#include <vector>

enum DIRECTION {UNDIR = 0, DIR = 1};

class Graph {
    DIRECTION dir;
    unsigned int node_count; // node limit to 4.3e9
    unsigned long long edge_count; // edge limit to 1.8e19
    double transmit_prob;
    unsigned int reps;
    std::vector<std::vector<unsigned int>> edge_list; // TODO: adjacency list vs. matrix ?
    
    void addEdge(unsigned int, unsigned int, DIRECTION);
    void delEdge(unsigned int, unsigned int, DIRECTION);
    
public:
    Graph(unsigned int, double);
    void setGraph(unsigned int, DIRECTION);
    unsigned int get_node_count();
    unsigned long long get_edge_count();
    
    void readFromFile(std::string inputFile);
    void printGraph(); // for testing small graphs
};

#endif /* graph_hpp */
