#ifndef Solver_H
#define Solver_H
#define START_POINT 0
#define CAN_SOLVE 1
#define CANT_SOLVE -1

#include "../data/Maze.h"
#include "../data/Edge.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
class Solver{
	protected:
		int xStart = 0;
		int yStart = 0;
		int xFinish;
		int yFinish;
		std::vector<Edge> path;
		Maze maze;
		string fileName;
	
	public:
		virtual int solve()=0;
		Solver(Maze & m, string name)
		{
			xFinish = m.getWidth()-1;
			yFinish = m.getHeight()-1;
			maze = m;
			fileName = name;
		}
		
		void drawPath( );
};

#endif
