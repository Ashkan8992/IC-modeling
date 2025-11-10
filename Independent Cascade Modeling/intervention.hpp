//  intervention.hpp
//  Independent Cascade Modeling
//
//  Created by Ashkan Bashardoust on 11/5/25.

#ifndef intervention_hpp
#define intervention_hpp

#include "simulation.hpp"

void myOpic(Sim&, int); // Each rounds picks the min access node as next sourse
void naive_myOpic(Sim&, int); // Picks the k min access nodes as sourses

void reach(Sim&, int); // Each round picks the source that maximizes the influence
void naiveReach(Sim&, int); // Picks the k nodes that maximizes the influence

#endif /* intervention_hpp */
