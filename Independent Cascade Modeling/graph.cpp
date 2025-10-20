//  graph.cpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/15/25.

#include "graph.hpp"
    
void Graph::addEdge(unsigned int u, unsigned int v) {
    if (edgeExist(u, v)) { return; }
    
    edge_list[u].push_back(v);
    
    if (dir == UNDIR) {
        edge_list[v].push_back(u);
    }
    
    this->edge_count++;
}

void Graph::delEdge(unsigned int u, unsigned int v) {
    if (!edgeExist(u, v)) { return; }
    
    edge_list[u].erase(std::remove(edge_list[u].begin(), edge_list[u].end(), v), edge_list[u].end());
    
    if (dir == UNDIR) {
        edge_list[v].erase(std::remove(edge_list[v].begin(), edge_list[v].end(), u), edge_list[v].end());
    }
    
    this->edge_count--;
}

bool Graph::edgeExist(unsigned int u, unsigned int v) {
    return std::find(edge_list[u].begin(), edge_list[u].end(), v) != edge_list[u].end();
}

void Graph::addRandEdg(unsigned int u) {
    unsigned int v;
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<unsigned int> distr(0, node_count - 1);
    
    if (u == UINT_MAX) { u = distr(generator); }
    do {
        v = distr(generator);
    } while(u == v || edgeExist(u, v));
    
    std::cout << "Edge Added: " << u << " " << v << std::endl;
    addEdge(u, v);
}
    
Graph::Graph() : node_count(0), dir(UNDIR), edge_count(0) {}

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

const std::vector<unsigned int>& Graph::get_neighbors(unsigned int u) {
    return edge_list[u];
}

// TODO: nodes are assumed to be labeled 0 to n-1
void Graph::readFromFile(std::string inputFileName) {
    std::ifstream inputFile;
    inputFile.open(inputFileName);
    
    if (!inputFile) {
        throw std::ios_base::failure("Failed to open file: " + inputFileName);
    }
    
    unsigned int n, d; // TODO: try-catch for n ?
    unsigned long long m;
    inputFile >> n >> d >> m;
    if (d != 0 && d != 1) { std::cerr << "Invalid argument: Direction 0 for undir or 1 dir" << std::endl; }
    DIRECTION dir = static_cast<DIRECTION>(d);
    
    this->setGraph(n, static_cast<DIRECTION>(dir));
    
    unsigned int u, v;  // TODO: try-catch for u, v ?
    while (inputFile >> u >> v) {
        this->addEdge(u, v);
    }
    
    if (m != edge_count) { // sanity check
        std::cerr << "Invalid argument edge count: " << m << " counted as: " << edge_count << std::endl;
    }
    
    std::cout << "Graph loaded successfully!" << std::endl;
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
