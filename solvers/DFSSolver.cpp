#include "DFSSolver.h"

using namespace std;

int DFSSolver::solve()
{
	//clock_t variables to record time required for the solver
	auto tStart = chrono::high_resolution_clock::now();
	Cell* currentCell, *neighbourCell; //pointers for looping
	// boolean to keep track whether there was any visited neighbour
	bool neighboursVisited = false; 
	//vector of Cell to keep track of pathway
	vector<Cell> pathCells;
	//initializing currentCell to starting cell
	currentCell = &maze.cells[yStart][xStart];
	currentCell ->visited = true;
	pathCells.push_back(maze.cells[yStart][xStart]);
	
	//does the loop while it hasn't reached the destination cell
	int currentX = xStart, currentY = yStart;
	while(currentX != xFinish || currentY != yFinish)
	{
		//setting neighboursVisited to false to indicate 
		//that no neighbour has been visited yet
		neighboursVisited = false;
		for(auto i = currentCell->neighbours.begin(); 
				i<currentCell->neighbours.end(); i++)
		{
			neighbourCell = *i;
			//if current neighbor cell hasn't been visited yet
			if(neighbourCell->visited == false)
			{
				//create edge
				Edge e;
				e.xCellA = currentCell->x;
				e.yCellA = currentCell->y;
				e.xCellB = neighbourCell ->x;
				e.yCellB = neighbourCell->y;
				//change the current cell
				currentCell = &maze.cells[neighbourCell->y][neighbourCell->x];
				//change value of visited
				neighbourCell->visited = true;
				//add to pathway & vector of cell to keep track
				pathCells.push_back(*currentCell);
				path.push_back(e);
				neighboursVisited = true;
				currentX = neighbourCell->x;
				currentY = neighbourCell->y;
				break;
			}
			
		}
		//if no neighbours are visited, trace back one time by deleting 
		//the last element of both pathway and order of cell
		if(!neighboursVisited)
		{
			pathCells.pop_back();
			path.pop_back();
			if(path.empty())
				currentCell = &maze.cells[xStart][yStart];
			currentCell = &(pathCells.back());
		}
	}
	//calculating time taken to solve maze
	auto tEnd = chrono::high_resolution_clock::now();
	auto diff =chrono::duration_cast<chrono::microseconds>(tEnd-tStart);
	cout<<"Time taken to solve : "<< diff.count() << " microseconds"<<endl;
	
	//calculate time to draw path
	tStart = chrono::high_resolution_clock::now();
	//draws the path over the maze
	drawPath();
	tEnd = chrono::high_resolution_clock::now();
	diff =chrono::duration_cast<chrono::microseconds>(tEnd-tStart);
	cout<<"Time taken to write SVG : "<< diff.count() << " microseconds"<<endl;
	
	return CAN_SOLVE;
}