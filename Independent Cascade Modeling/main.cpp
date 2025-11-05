//  main.cpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/15/25.

#include "graph.hpp"
#include "intervention.hpp"
#include "simulation.hpp"

int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false); // disables synchronization of C++ standard streams and C
    // std::cin.tie(nullptr); // TODO: needed?
    
    if (argc != 9) { // Sanity check
        std::cerr << "Input Format: <Input File>, <Output File>, <Transmission Prob>, <Repetitions>, <Seeding Mode>, <Seed Count>, <New Seed Count>" << std::endl;
        exit(1);
    }
    
    double alpha; // Read trasmit prob
    try {
        alpha = std::stod(argv[3]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    if (alpha <= 0.0 || alpha > 1.0) {
        std::cerr << "Propagation probability p must be in (0,1].\n";
    }
    std::cout << "Transmission Prob: " << alpha << std::endl;
    
    int num_threads; // Read thread count
    try {
        num_threads = std::stoi(argv[4]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    if (num_threads == 0) { num_threads = std::thread::hardware_concurrency() / 2; } // fallback default TODO: Which is faster?
    std::cout << "Threads Count: " << num_threads << std::endl;
    
    size_t reps; // Read simulation count
    try {
        reps = std::stoi(argv[5]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    if (reps % num_threads != 0) { std::cerr << "Simulation Reps not diviseble by thread count.\n"; }
    std::cout << "Number of Runs (samples): " << reps << std::endl;
    
    std::string seed_mode = argv[6];
    std::cout << "Seeding mode selected: " << seed_mode << std::endl;
    
    
    int init_k; // Read number of seeds
    try {
        init_k = std::stoi(argv[7]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    std::cout << "Seed Count: " << init_k << std::endl;
    
    int k; // Read number of added seeds
    try {
        k = std::stoi(argv[8]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    std::cout << "New Seeds Required: " << k << std::endl;
    
    Graph g; // Define network
    
    std::string inputFile = argv[1]; // Read network
    g.readFromFile(inputFile);
    // std::cout << "From: " << inputFile << std::endl;
    
    Sim sim(g, reps, alpha, init_k, seed_mode, num_threads); // Setup simulation
    
    // sim.runParallelSim();
    naive_myOpic(sim, k);
    
    std::string outputFile = argv[2];
    sim.printAccessProbs(outputFile); // output access probs
    // std::cout << "Access results outputed in: " << outputFile << std::endl;
    
    return EXIT_SUCCESS;
}
