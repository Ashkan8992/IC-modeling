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
    int node_count; // node limit to 4.3e9
    long long edge_count; // edge limit to 1.8e19
    std::vector<std::vector<int>> edge_list; // sparse: adjacency list, dense: bool matrix
    
public:
    Graph();
    void setGraph(int, DIRECTION); // Couldn't include in the Constructor as it needs to read the graph first
    int get_node_count() const;
    long long get_edge_count() const;
    const std::vector<int>& get_neighbors(int) const;
    
    void addEdge(int, int);
    void delEdge(int, int);
    bool edgeExist(int, int);
    void addRandEdg(int = UINT_MAX); // Option to fix the source or completely at random (pass u or UINT_MAX)
    
    void readFromFile(std::string inputFile); // Format: n, m, dir, ... (edge list: u, v)
    void printGraph(); // For testing small graphs
};

#endif /* graph_hpp */
