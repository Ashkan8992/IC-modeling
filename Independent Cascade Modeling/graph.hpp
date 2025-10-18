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
    std::vector<std::vector<unsigned int>> edge_list; // TODO: adjacency list vs. bool matrix? former for sparse graphs - latter for dense
    
    void addEdge(unsigned int, unsigned int, DIRECTION);
    void delEdge(unsigned int, unsigned int, DIRECTION);
    
public:
    Graph();
    void setGraph(unsigned int, DIRECTION);
    unsigned int get_node_count();
    unsigned long long get_edge_count();
    const std::vector<unsigned int>& get_neighbors(unsigned int);
    
    void readFromFile(std::string inputFile);
    void printGraph(); // for testing small graphs
};

#endif /* graph_hpp */
