#include "solver.h"

void Solver::drawPath()
{
	std::vector<Edge> edges = maze.edges;
	int width = xFinish + 1;
	//opening SVG files to write data into
	ofstream file(fileName.c_str());
	//writing width and height with SVG format
	file << "<svg width='"<< MAZE_SIZE <<"' height='"<< MAZE_SIZE 
		<<"' xmlns='http://www.w3.org/2000/svg'>"<<endl;
	file << "<rect width='"<< MAZE_SIZE <<"' height ='"<< MAZE_SIZE 
		<<"' style='fill:black'/>"<<endl;
	//iterates through each edge in the maze to print its datas
	for(Edge e: edges)
	{
		file <<"<line stroke='white' stroke-width='"
			<<(float)MAZE_SIZE/(width*2)<<"' ";
		file << "x1= '"<< (float)e.xCellA / width * MAZE_SIZE<<"' ";
		file << "y1= '"<< (float)e.yCellA / width * MAZE_SIZE<<"' ";
		file << "x2= '"<< (float)e.xCellB / width * MAZE_SIZE<<"' ";
		file << "y2= '"<< (float)e.yCellB / width * MAZE_SIZE<<"' ";
		file << "/>"<<endl;
	}
	for(Edge e: path)
	{
		file <<"<line stroke='red' stroke-width='"
			<<(float)MAZE_SIZE/(width*2)<<"' ";
		file << "x1= '"<< (float)e.xCellA / width * MAZE_SIZE<<"' ";
		file << "y1= '"<< (float)e.yCellA / width * MAZE_SIZE<<"' ";
		file << "x2= '"<< (float)e.xCellB / width * MAZE_SIZE<<"' ";
		file << "y2= '"<< (float)e.yCellB / width * MAZE_SIZE<<"' ";
		file << "/>"<<endl;
	}
	file<<"</svg>";
}
