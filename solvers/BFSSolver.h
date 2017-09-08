#ifndef BFSSolver_H
#define BFSSolver_H

#include "solver.h"
#include "../data/Maze.h"
#include "../data/Cell.h"
#include<queue>
#include<chrono>
using namespace std;
class BFSSolver : public Solver{
protected:
	vector<vector<Cell>> visited;
public:
	virtual int solve ();
	BFSSolver(Maze & maze, std::string name) 
	: Solver::Solver (maze, name){};
	
};

#endif