//  main.cpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/15/25.

#include "graph.hpp"
#include "simulation.hpp"

int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false); // disables synchronization of C++ standard streams and C
    // std::cin.tie(nullptr);
    
    if (argc != 8) { // Sanity check
        std::cerr << "Input Format: <Input File>, <Output File>, <Transmission Prob>, <Repetitions>, <Seeding Mode>, <Seed Count>" << std::endl;
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
    std::cout << "Number of Threads: " << num_threads << std::endl;
    
    size_t reps; // Read simulation count
    try {
        reps = std::stoi(argv[5]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    if (reps % num_threads != 0) { std::cerr << "Simulation Reps not diviseble by thread count.\n"; }
    std::cout << "Number of Repetitions: " << reps << std::endl;
    
    std::string seed_mode = argv[6];
    
    int k; // Read number of seeds
    try {
        k = std::stoi(argv[7]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    
    Graph g; // Define network
    
    std::string inputFile = argv[1]; // Read network
    g.readFromFile(inputFile);
    // std::cout << "Network: " << inputFile << std::endl;
    
    Sim sim(g, reps, alpha, k, seed_mode); // Setup simulation
    
    sim.runParallelSim(num_threads);
    
    std::string outputFile = argv[2];
    sim.printAccessProbs(outputFile);
    
    return EXIT_SUCCESS;
}
