//  graph.hpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/15/25.

#ifndef graph_hpp
#define graph_hpp

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

enum DIRECTION {UNDIR = 0, DIR = 1};

class Graph {
    DIRECTION dir;
    unsigned int node_count; // node limit to 4.3e9
    unsigned long long edge_count; // edge limit to 1.8e19
    // TODO: adjacency list (sparse?) vs. bool matrix (dense)?
    std::vector<std::vector<unsigned int>> edge_list;
    
public:
    Graph();
    void setGraph(unsigned int, DIRECTION); // Couldn't include in the Constructor as it needs to read the graph first
    unsigned int get_node_count();
    unsigned long long get_edge_count();
    const std::vector<unsigned int>& get_neighbors(unsigned int);
    
    void addEdge(unsigned int, unsigned int);
    void delEdge(unsigned int, unsigned int);
    bool edgeExist(unsigned int, unsigned int);
    void addRandEdg(unsigned int = UINT_MAX); // Option to fix the source or completely at random
    
    void readFromFile(std::string inputFile); // Format: n, m, dir, ... (edge list: u, v)
    void printGraph(); // For testing small graphs
};

#endif /* graph_hpp */
