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
    // TODO: group? wight? threshold?
    DIRECTION dir;
    int node_count; // node limit to 4.3e9
    long long edge_count; // edge limit to 1.8e19
    std::vector<std::vector<int>> edge_list; // sparse: adjacency list, dense: bool matrix
    
public:
    Graph();
    void setGraph(int, DIRECTION); // Couldn't include in the Constructor as it needs to read the graph first
    int get_node_count() const; // Return #nodes
    long long get_edge_count() const; // Return #edges
    const std::vector<int>& get_neighbors(int) const; // Return list of neighbors
    
    void addEdge(int, int); // Add an edge
    void delEdge(int, int); // Remove an edge
    bool edgeExist(int, int); // Return if edge exists
    void addRandEdg(int = UINT_MAX); // Add random edge: Option to fix the source or completely at random (pass u or UINT_MAX)
    
    void readFromFile(std::string inputFile); // Read graph - Format: n, m, dir, ... (edge list: u, v)
    void printGraph(); // For testing small graphs
};

#endif /* graph_hpp */
