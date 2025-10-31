//  graph.cpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/15/25.

#include "graph.hpp"
    
void Graph::addEdge(int u, int v) {
    if (edgeExist(u, v)) { return; }
    
    edge_list[u].push_back(v);
    
    if (dir == UNDIR) {
        edge_list[v].push_back(u);
    }
    
    this->edge_count++;
}

void Graph::delEdge(int u, int v) {
    if (!edgeExist(u, v)) { return; }
    
    edge_list[u].erase(std::remove(edge_list[u].begin(), edge_list[u].end(), v), edge_list[u].end());
    
    if (dir == UNDIR) {
        edge_list[v].erase(std::remove(edge_list[v].begin(), edge_list[v].end(), u), edge_list[v].end());
    }
    
    this->edge_count--;
}

bool Graph::edgeExist(int u, int v) {
    return std::find(edge_list[u].begin(), edge_list[u].end(), v) != edge_list[u].end();
}

void Graph::addRandEdg(int u) {
    int v;
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(0, node_count - 1);
    
    if (u == UINT_MAX) { u = distr(generator); }
    do {
        v = distr(generator);
    } while(u == v || edgeExist(u, v));
    
    std::cout << "Edge Added: " << u << " " << v << std::endl;
    addEdge(u, v);
}
    
Graph::Graph() : node_count(0), dir(UNDIR), edge_count(0) {}

void Graph::setGraph(int n, DIRECTION d) {
    this->node_count = n;
    this->dir = d;
    
    edge_list.resize(n);
}

int Graph::get_node_count() const {
    return node_count;
}

long long Graph::get_edge_count() const {
    return edge_count;
}

const std::vector<int>& Graph::get_neighbors(int u) const {
    return edge_list[u];
}

// TODO: nodes are assumed to be labeled 0 to n-1
void Graph::readFromFile(std::string inputFileName) {
    std::ifstream inputFile;
    inputFile.open(inputFileName);
    
    if (!inputFile) {
        throw std::ios_base::failure("Failed to open file: " + inputFileName);
    }
    
    int n, d; // TODO: try-catch for n ?
    long long m;
    inputFile >> n >> d >> m;
    if (d != 0 && d != 1) { std::cerr << "Invalid argument: Direction 0 for undir or 1 dir" << std::endl; }
    DIRECTION dir = static_cast<DIRECTION>(d);
    
    this->setGraph(n, static_cast<DIRECTION>(dir));
    
    int u, v;
    while (inputFile >> u >> v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            throw std::ios_base::failure("Invalid edge argument: (" + std::to_string(u) + ", " + std::to_string(v) + ")\n");
        }
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
    for (size_t v = 0; v < edge_list.size(); ++v) {
        std::cout << v << ": ";
        for (auto u : edge_list[v]) {
            std::cout << u << " ";
        }
        std::cout << std::endl;
    }
}
