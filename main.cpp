//
//  main.cpp
//  MazeSolver
//
//  Created by Harneet Kaur on 11/3/18.
//  Copyright © 2018 Harneet Kaur. All rights reserved.
//

#include <iostream>
#include "MazeSolver.h"

using std::cout;
using std::endl;

int main() {

    MazeSolver solver("input.txt");
    
    if(solver.mazeIsReady())
    {
        solver.solveMaze();
        solver.printSolution();
    }
    
    return 0;
}
