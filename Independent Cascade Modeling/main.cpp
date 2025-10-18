//  main.cpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 10/15/25.

#include "graph.hpp"
#include "simulation.hpp"

int main(int argc, const char * argv[]) {
    
    if (argc != 4) { // Sanity check
        std::cerr << "Input Format: Input File, Transmission Prob, Repetitions" << std::endl;
        exit(1);
    }
    
    double alpha; // Read trasmit prob
    try {
        alpha = std::stod(argv[2]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    std::cout << "Transmission Prob: " << alpha << std::endl;
    
    unsigned int reps; // Read simulation count
    try {
        reps = std::stoi(argv[3]); // TODO: int conversion to unsigned int
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    std::cout << "Number of Repetitions: " << reps << std::endl;
    
    Graph g; // Define network
    
    std::string inputFile = argv[1]; // Read network
    g.readFromFile(inputFile);
    // std::cout << "Network: " << inputFile << std::endl;
    
    Sim sim(g, reps, alpha); // Setup simulation
    
    sim.runMonteCarloSim();
    sim.printAccessProbs();
    
    return EXIT_SUCCESS;
}
