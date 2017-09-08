#include "ABGenerator.h"
using namespace std;
//method to generate maze
bool ABGenerator::generate()
{
	//variable to record time
	auto tStart = chrono::high_resolution_clock::now();
	
    Cell* tempCell;
    Cell* loopCell;
    int edgesCreated = 0;
    int expectedEdges = (*maze).getWidth() * (*maze).getHeight() - 1;
    int width = (*maze).getWidth();
    int height = (*maze).getHeight();
    unsigned int a,b, randomNeighbour = MAX_NEIGHBOUR;
    //new mt19937 object created with existing seed
    mt19937 random(seed);
    //creating objects of uniform_int_distribution 
	//to limit the minimum and maximum value
    uniform_int_distribution<int> initWidthLimit(0, width-1);
    uniform_int_distribution<int> initHeightLimit(0, height-1);
    //generating a pseudo random number as initial coordinate,
	//and save the cell of that coordinate to tempCell
    a = initWidthLimit(random);
    b = initHeightLimit(random);
    tempCell = &(maze -> cells[a][b]);
    tempCell->visited = true;
    uniform_int_distribution<int> neighbourCell(0, MAX_NEIGHBOUR - 1);
    //it will do the loop until the expected edges value is met
    while(edgesCreated <expectedEdges)
    {
        //nested loop to retrieve a random neighbour
        do
        {
            randomNeighbour = neighbourCell(random);
        }
        while(randomNeighbour > (tempCell->adjCell.size()-1 ));
        //getting the neighbour
        loopCell = tempCell->adjCell[randomNeighbour];
        //if it hasn't been visited yet, mark visited 
		//and create an edge of it and the current cell
        if(loopCell->visited == false)
        {
            loopCell->visited = true;
            Edge edge;
            edge.xCellA = tempCell->x;
            edge.yCellA = tempCell->y;
            edge.xCellB = loopCell->x;
            edge.yCellB = loopCell->y;
            edgesCreated++;
            (maze -> edges).push_back(edge);
        }
        //change the current cell (tempCell) to the new cell
        tempCell = loopCell;		
	}
		//calculating time taken and printing the result
	auto tEnd = chrono::high_resolution_clock::now();
	auto diff =chrono::duration_cast<chrono::microseconds>(tEnd-tStart);
	cout<<"Time taken to generate : "<< diff.count() << " microseconds"<<endl;
	maze->setNeighbours();
	return true;
}