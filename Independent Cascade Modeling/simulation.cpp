//  simulation.cpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/16/25.

#include "simulation.hpp"

// TODO: get argument to choose the type of source generation algorithm
Sim::Sim(Graph& g, unsigned int r, double alpha) : net(g), reps(r), transmit_prob(alpha) {
    access_probs.resize(g.get_node_count(), 0.0);
    generate_sources();
}

/* double Sim::get_alpha() {
    return transmit_prob;
} */

void Sim::generate_sources() {
    sources = std::vector<int> (1, 0);
}

void Sim::runMonteCarloSim() {
    // Set random generator: Undeterministic
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(0.0, 1.0);
    
    // Each Monte Carlo Simulation
    for (int iter = 0; iter < reps; ++iter) {
        
        std::vector<bool> visited(net.get_node_count(), false);
        
        std::queue<int> bfs;
        for (auto src : sources) {
            bfs.push(src);
            visited[src] = true;
            ++access_probs[src];
        }
        
        // Run the IC spread
        while (!bfs.empty()) {
            int currNode = bfs.front();
            
            // Iterate over neighbors
            for (auto neighbor : net.get_neighbors(currNode)) {
                if (visited[neighbor]) { continue; }
                if (distr(generator) <= transmit_prob) {
                    visited[neighbor] = true;
                    bfs.push(neighbor);
                    ++access_probs[neighbor];
                }
            }
            bfs.pop();
        }
    } // One IC model done
    
    // Divide to get the probability
    for (auto &prob : access_probs) {
        prob = prob / static_cast<double>(reps);
    }
}

void Sim::printAccessProbs() {
    for (int i = 0; i < net.get_node_count(); ++i) {
        std::cout << i << " access: " << access_probs[i] << std::endl;
    }
}
