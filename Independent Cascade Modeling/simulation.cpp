//  simulation.cpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/16/25.

#include "simulation.hpp"

Sim::Sim(Graph& g, size_t r, double alpha, int cnt, std::string mode, int thread_count) :
        net(g), reps(r), transmit_prob(alpha), src_count(cnt), num_threads(thread_count) {
    access_probs.resize(g.get_node_count(), 0.0);
    generate_sources(mode);
}

int Sim::get_src_count() {
    return src_count;
}

Graph& Sim::get_graph() {
    return net;
}

// TODO: implement multiple options: Random, Max-Degree, Central, etc.
void Sim::generate_sources(std::string mode) {
    sources = std::vector<int> (1, 0);
    // sources.reserve(src_count);
}

void Sim::add_source(int src) {
    sources.push_back(src);
    ++src_count;
}

void Sim::runSim(size_t reps, std::vector<int> &local_count) {
    // Set random generator: Undeterministic
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(0.0, 1.0);
   
    // Each Monte Carlo Simulation
    for (size_t iter = 0; iter < reps; ++iter) {
        
        std::vector<bool> visited(net.get_node_count(), false);
        
        std::queue<int> bfs;
        for (auto src : sources) {
            bfs.push(src);
            visited[src] = true;
            ++local_count[src];
        }
        
        // Run the IC spread
        while (!bfs.empty()) {
            int currNode = bfs.front();
            bfs.pop();
            
            // Iterate over neighbors
            for (auto neighbor : net.get_neighbors(currNode)) {
                if (visited[neighbor]) { continue; }
                if (distr(generator) <= transmit_prob) {
                    visited[neighbor] = true;
                    bfs.push(neighbor);
                    ++local_count[neighbor];
                }
            }
        }
    } // One IC model done
}

void Sim::runParallelSim() {
    size_t reps_per_thread = reps / num_threads;
    std::vector<std::thread> threads;
    std::vector<std::vector<int>> local_counts(num_threads, std::vector<int>(net.get_node_count(), 0));
    
    // Launch worker threads
    for (unsigned int t = 0; t < num_threads; ++t) {
        threads.emplace_back(&Sim::runSim, this, reps_per_thread, std::ref(local_counts[t]));
    }

    // Join threads
    for (auto &th : threads) {
        th.join();
    }
    
    // Aggregate results
    access_probs.assign(net.get_node_count(), 0.0);
    for (unsigned int t = 0; t < num_threads; ++t) {
        for (size_t i = 0; i < access_probs.size(); ++i) {
            access_probs[i] += local_counts[t][i];
        }
    }

    // Normalize
    for (auto &prob : access_probs) {
        prob = prob / static_cast<double>(reps);
    }
}

void Sim::printAccessProbs(std::string outputFileName) {
    std::ofstream outputFile;
    outputFile.open(outputFileName);
    if (!outputFile) {
        throw std::ios_base::failure("Failed to open file: " + outputFileName);
    }
    
    for (size_t i = 0; i < net.get_node_count(); ++i) {
        outputFile << i << ": " << access_probs[i] << std::endl;
    }
    
    outputFile.close();
}
