#ifndef DjikstaSolver_H
#define DjikstraSolver_H

#include "solver.h"
#include "../data/Maze.h"
#include<time.h>
#include<chrono>
class DFSSolver: public Solver{
	protected:
	
	public:
		virtual int solve();
		DFSSolver(Maze & maze, std::string name) 
			: Solver::Solver (maze, name){};
};

#endif