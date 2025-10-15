//  graph.cpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/15/25.

#include "graph.hpp"
    
void Graph::addEdge(unsigned int u, unsigned int v, DIRECTION dir) {
    if (std::find(edge_list[u].begin(), edge_list[u].end(), v) != edge_list[u].end()) { return; }
    
    edge_list[u].push_back(v);
    
    if (dir == UNDIR) {
        edge_list[v].push_back(u);
    }
    
    this->edge_count++;
}
    
Graph::Graph(unsigned int r, double a) {
    this->reps = r;
    this->transmit_prob = a;
    this->edge_count = 0;
}

void Graph::setGraph(unsigned int n, DIRECTION d) {
    this->node_count = n;
    this->dir = d;
    
    edge_list.resize(n);
}

unsigned int Graph::get_node_count() {
    return node_count;
}

unsigned long long Graph::get_edge_count() {
    return edge_count;
}
    
void Graph::readFromFile(std::string inputFileName) {
    std::ifstream inputFile;
    inputFile.open(inputFileName);
    
    if (!inputFile) {
        std::cerr << "Unable to open file " << inputFileName << std::endl;
        exit(1);   // call system to stop
    }
    
    unsigned int n, d; // TODO: try-catch for n ?
    unsigned long long m;
    inputFile >> n >> d >> m;
    if (d != 0 && d != 1) { std::cerr << "Invalid argument: Direction 0 for undir or 1 dir" << std::endl; }
    DIRECTION dir = static_cast<DIRECTION>(d);
    
    this->setGraph(n, static_cast<DIRECTION>(dir));
    
    unsigned int u, v;  // TODO: try-catch for u, v ?
    while (inputFile >> u >> v) {
        this->addEdge(u, v, dir);
    }
    
    if (m != edge_count) { // sanity check
        std::cerr << "Invalid argument edge count: " << m << " counted as: " << edge_count << std::endl;
    }
    
    inputFile.close();
}

// for testing small graphs
void Graph::printGraph(){
    for (unsigned int v = 0; v < edge_list.size(); ++v) {
        std::cout << v << ": ";
        for (auto u : edge_list[v]) {
            std::cout << u << " ";
        }
        std::cout << std::endl;
    }
}
