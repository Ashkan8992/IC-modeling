//  intervention.cpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 11/5/25.

#include "intervention.hpp"

void myOpic(Sim& sim, int k) {
    
    for (int i = 0; i < k; ++i) {
        sim.runParallelSim();
        
        auto min_it = std::min_element(sim.access_probs.begin(), sim.access_probs.end());
        double min_value = *min_it;
        if (min_value == 1.0) {
            std::cerr << "No additional source needed\n";
            return;
        }
        int min_index = static_cast<int>(min_it - sim.access_probs.begin());
        sim.add_src(min_index);
        std::cout << "New source id: " << min_index << std::endl;
    }
    
    sim.runParallelSim(); // Update access probs
}

void naive_myOpic(Sim& sim, int k) {
    sim.runParallelSim();

    std::vector<std::pair<int, double>> pairs;
    pairs.reserve(sim.access_probs.size());
    for (int i = 0; i < sim.access_probs.size(); ++i)
        pairs.emplace_back(i, sim.access_probs[i]);

    auto comp = [](const auto& a, const auto& b) { return a.second < b.second; };

    std::nth_element(pairs.begin(), pairs.begin() + k, pairs.end(), comp);
    pairs.resize(k);
    
    for (auto pair : pairs) {
        sim.add_src(pair.first);
        std::cout << "New source id: " << pair.first << std::endl;
    }
    
    sim.runParallelSim(); // Update access probs
}

void reach(Sim& sim, int k) {
    
    for (int i = 0; i < k; ++i) {
        int next_src = 0;
        double max_influ = 0;
        
        for (int node = 0; node < sim.get_graph().get_node_count(); ++node) {
            if (sim.contain_src(node)) { continue; }
            sim.add_src(node);
            sim.runParallelSim();
            sim.remove_src(node);
            if (max_influ < sim.get_average()) {
                max_influ = sim.get_average();
                next_src = node;
            }
        }
        sim.add_src(next_src);
        std::cout << "New source id: " << next_src << std::endl;
    }
    
    sim.runParallelSim(); // Update access probs
}

void naiveReach(Sim& sim, int k) {
    
}
