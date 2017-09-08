#include "BFSSolver.h"
#define START_POINT 0
#define CAN_SOLVE 1
#define CANT_SOLVE -1

using namespace std;


int BFSSolver::solve()
{
	// Variables
	//clock_t variables to record time required for the solver
	auto tStart = chrono::high_resolution_clock::now();
	visited = maze.cells; // Check Visited Cell
	queue<Cell*> cells_queue; // Expansion area 
	vector<Cell *> pathway_queue ;
	Cell * current_cell = nullptr; // Current Cell
	Cell last_cell , *neighbour_cell;

	// Initializes Cell
	visited[START_POINT][START_POINT].visited = true;
	current_cell = &visited[START_POINT][START_POINT];  
	last_cell.x = xFinish;
	last_cell.y = yFinish;
	current_cell->parent = nullptr;
	current_cell->visited = true;

	// Mark the current node as visited and enqueue it 
	cells_queue.push(current_cell);
	pathway_queue.push_back(current_cell);


	// While we have cells 
	while(!cells_queue.empty())
	{
		// Grab the First
		current_cell = cells_queue.front();
		cells_queue.pop();

		// Reach the last cell = Problem Solved !
		if(current_cell->x == last_cell.x && current_cell->y == last_cell.y)
		{
			// Print The PathSaver 
			vector<Cell*>real_path;
			Cell* current;
			for(unsigned int i = 0 ; i < pathway_queue.size() ; i++)
			{
				if(pathway_queue[i]->x == xFinish
					&& pathway_queue[i]->y == yFinish)
				{
					current = pathway_queue[i];
				}

			}
			while(current->parent!=nullptr)
			{
					Edge e;// Initialize to empty again
					// Set A point 
					e.xCellA = current->x;
					e.yCellA = current->y;
					// Set B Point
					e.xCellB = current->parent->x;
					e.yCellB = current->parent->y;

					path.push_back(e);
					real_path.push_back(current->parent);
					current = current->parent;
			}
			//calculating time taken to solve maze
			auto tEnd = chrono::high_resolution_clock::now();
			auto diff =chrono::duration_cast<chrono::microseconds>(tEnd-tStart);
			cout<<"Time taken to solve : "<< diff.count() << " microseconds"<<endl;
			
			//calculate time to draw path
			tStart = chrono::high_resolution_clock::now();
			//draws the path over the maze
			drawPath(); // Path is vector<Edges>
			tEnd = chrono::high_resolution_clock::now();
			diff =chrono::duration_cast<chrono::microseconds>(tEnd-tStart);
			cout<<"Time taken to write SVG : "<< diff.count() << " microseconds"<<endl;
			
			return CAN_SOLVE;
		}
		else
		{
			// Find Unvisited Neighbour
			for(auto i = current_cell->neighbours.begin();
				i!=current_cell->neighbours.end(); i++)
			{
				neighbour_cell = *i;
				// If it not visited -> mark it and add to queue

				if(neighbour_cell->visited == false)
				{
					
					neighbour_cell->visited = true ; // Mark it as visited 
					neighbour_cell->parent = current_cell;
					cells_queue.push(neighbour_cell);
					pathway_queue.push_back(neighbour_cell);
				
				}
				 
			}
		}

	}

	return CANT_SOLVE;
}
