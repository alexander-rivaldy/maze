#include "EllerGenerator.h"
using namespace std;

bool EllerGenerator::generate()
{
	//variable to record time
	auto tStart = chrono::high_resolution_clock::now();
	
	//variables to randomise connection
    uniform_int_distribution<int> boolean(0, 1); 
    mt19937 random(seed);
	//getting width and height
    int width = (*maze).getWidth();
    int height = (*maze).getHeight();
	//indicators for various conditions
    int connected = 0, currentHt = 0; 
	bool vertical = true;
	int i, j, x,currentWidth; //loop counters
	//temporary variables to store set numbers
	int tempSetNumber1 = 0, tempSetNumber2 = 0; 
	//variable to keep track which set number hasn't been used
	int setNumberCounter = 1; 
	vector<vector<int>> setNumbers;//2d array to store set numbers of each cell
	vector<vector<bool>> visited; //2d array to store visited value of each cell
	//vector to contain check value whether the current set 
	//has satisfy the minimum vertical connection
	vector<bool> minimumVertical; 
	
	//initialising all cells set numbers to 0
	for(i = 0; i < height ; i++)
	{
		vector<int> set;
		for(j = 0; j < width; j++)
		{
			set.push_back(0);
		}
		setNumbers.push_back(set);
	}
	
	//initialising all cells visited to false
	for(i = 0; i < height; i++)
	{
		vector<bool> visitedRow;
		for(j=0; j<width; j++)
		{
			visitedRow.push_back(false);
		}
		visited.push_back(visitedRow);
	}
	
	//loops as many as the height
	for(currentHt = 0 ; currentHt < height ; currentHt++)
	{
		//creates random connection for each cell in the row
		for(currentWidth = 0; currentWidth < width; currentWidth++)
		{
			//cout<<"ROW : " <<currentHt << " COLUMN : " <<currentWidth<<endl;
			//determining the random connection
			connected = boolean(random);
			if(currentHt == height-1)
				connected = 1;
			//special case when it's the first cell of the row
			if(currentWidth == 0)
			{
				//adds cell to a new set if it's not already in a set
				if(!visited[currentHt][currentWidth])
				{
					setNumbers[currentHt][currentWidth] = setNumberCounter;
					setNumberCounter++;
					visited[currentHt][currentWidth] = true;
				}
				continue;
			}
			//skips the cell if it's already connected to another set
			if(setNumbers[currentHt][currentWidth] == 
				setNumbers[currentHt][currentWidth-1])
				continue;
			//if current cell is connected to its left neighbour 
			//and left neighbour is already in a set, 
			//add the cell to the same set
			if(connected == 1 && visited[currentHt][currentWidth-1] 
				&& !visited[currentHt][currentWidth])
			{
				Edge e;
				e.xCellA = currentWidth;
				e.yCellA = currentHt;
				e.xCellB = currentWidth - 1;
				e.yCellB = currentHt;
				(maze -> edges).push_back(e);
				
				visited[currentHt][currentWidth] = true;
				setNumbers[currentHt][currentWidth] = 
					setNumbers[currentHt][currentWidth-1];
				
			}
			//if current cell is connected to its left neighbour 
			//and both of them are already in different sets,
			//merge the sets into a new one
			else if(connected == 1 && visited[currentHt][currentWidth-1] 
				&& visited[currentHt][currentWidth])
			{
				Edge e;
				e.xCellA = currentWidth;
				e.yCellA = currentHt;
				e.xCellB = currentWidth - 1;
				e.yCellB = currentHt;
				(maze -> edges).push_back(e);
				
				tempSetNumber1 = setNumbers[currentHt][currentWidth-1];
				tempSetNumber2 = setNumbers[currentHt][currentWidth];
				
				for(i = 0; i < height ; i++)
				{
					for(j = 0; j < width; j++)
					{
						if(setNumbers[i][j] == tempSetNumber1
							|| setNumbers[i][j] == tempSetNumber2)
							setNumbers[i][j] = setNumberCounter;
					}
				}
				setNumberCounter++;
			}
			//if current cell is not connected to its left neighbour, 
			//and current cell is not visited yet,
			//add current cell to a new set
			else if(connected == 0 && !visited[currentHt][currentWidth])
			{
				visited[currentHt][currentWidth]  = true;
				setNumbers[currentHt][currentWidth] = setNumberCounter;
				setNumberCounter++;
			}
			//if current cell is not connected to its left neighbour 
			//and current cell is already visited / already in a set
			//go to next iteration
			else if(connected == 0 && visited[currentHt][currentWidth] )
				continue;
		}
		
		//if current row is the last row, break out of the loop 
		//to skip the vertical connection
		if(currentHt == height-1)
			break;
		
		//initialising the minimum vertical of each cells in the row to false
		for(i = 0; i < width; i++)
		{
			minimumVertical.push_back(false);
		}
		
		//do the loop while minimum vertical is not satisfied yet
		// minimum vertical is at least 1 connection to the row below 
		//for each set in the current row
		do
		{
			for(i = 0; i < width; i++)
			{
				//do random connection if minimum vertical has not yet satisfied
				if(!minimumVertical[i])
				{
					connected = boolean(random);
					if(connected == 1)
					{
						Edge e;
						e.xCellA = i;
						e.yCellA = currentHt;
						e.xCellB = i;
						e.yCellB = currentHt + 1;
						(maze -> edges).push_back(e);
						setNumbers[currentHt + 1][i] 
							= setNumbers[currentHt][i];
						minimumVertical[i] = true;
						visited[currentHt+1][i] = true;
					}
				}
			}
			
			//checking whether a cell that has a vertical connection shares 
			//the same set number with another cell in the same row
			//if yes, then make the other cell minimum vertical to true
			for(i = 0; i < width; i++)
			{
				if(!minimumVertical[i])
				{
					x = setNumbers[currentHt][i];
					for(j = 0; j < width; j++)
					{
						if(setNumbers[currentHt][j] == x 
							&& minimumVertical[j])
						{
							minimumVertical[i] = true;
							break;
						}
					}
				}
			}
			
			//checking whether all sets have satisfied 
			//the minimum vertical connection
			vertical = true;
			for(i = 0; i < width; i++)
			{
				if(!minimumVertical[i])
					vertical = false;
			}
		}
		while(!vertical);
		
		//clearing the minimumVertical variable for the next row to use
		minimumVertical.clear();
	}
	maze->setInitialized(true);
	
	//calculating time taken and printing the result
	auto tEnd = chrono::high_resolution_clock::now();
	auto diff =chrono::duration_cast<chrono::microseconds>(tEnd-tStart);
	cout<<"Time taken : "<< diff.count() << " microseconds"<<endl;
	maze->setNeighbours();
	return true;
}

 


int EllerGenerator::checkVertical(vector<Cell*> set, int row)
{
    for(Cell* cell: set)
    {
        if(cell->south && cell->y == row)
            return 1;
    }
	return 0;
}

int EllerGenerator::findSetNumber(vector<vector<Cell*>> sets, int x, int y)
{
	for(vector<Cell*>::size_type j = 0; j < sets.size(); j++)
	{
		for(Cell* cell : sets[j])
		{
			if ( cell->x == x && cell->y == y)
				return j;
		}
	}
	return -1;
}




