#include "Maze.h"

//apply methods here
using namespace std;
Maze::Maze()
{
}

Maze::Maze(int w, int h)
{
    width= w;
    height = h;
    noEdges = width * height - 1;
    generateCells();
	setNeighbours();
	setAdjCells();
	initialize = true;
}

//method for maze that takes width and height as 
//parameters and asssigns them to the object
void Maze::setupData(int w, int h)
{
    width= w;
    height = h;
    noEdges = width * height - 1;
    generateCells();
	setNeighbours();
	setAdjCells();
	initialize = true;
}

//loading from binary file
bool Maze::loadBinaryFile(string fileName)
{
    int xA,yA,xB,yB, counter=0;
    uint32_t a;
	//checking whether the file is available
	ifstream ifile(fileName.c_str());
	if(!ifile)
		return false;
    //opening file with binary format
    FILE * file = fopen(fileName.c_str(),"r");
    ifstream in(fileName, ios::binary);
    //while there are more to read, 
	//read and save first three to width height and number of edges
    //and the rest of the ints would be saved as edges 
	//ONLY if there are 4 of them 
    //because binary file produces an extra int at the end of the file
    while(!feof(file))
    {
        fread(&a, sizeof(a), 1, file);
        //cout<<a<<" ";
        switch(counter)
        {
            case 0:
                width = a;
                break;
            case 1:
                height = a;
                break;
            case 2:
                noEdges = a;
                break;
            case 3:
                xA=a;
                break;
            case 4:
                yA=a;
                break;
            case 5:
                xB=a;
                break;
            case 6:
                yB=a;
                counter = 2;
                Edge edge;
                edge.xCellA = xA;
                edge.yCellA = yA;
                edge.xCellB = xB;
                edge.yCellB = yB;
                edges.push_back(edge);
                break;
        }
        counter++;
    }
    fclose(file);
	generateCells();
	setNeighbours();
	initialize = true;
	return true;
}

//saving to binary file
bool Maze::saveBinaryFile(string fileName)
{
    int xA,yA,xB,yB;
    //opening file with binary format
    ofstream stream(fileName, ios::binary);
    //write width height and number of edges
    stream.write(reinterpret_cast<const char*> (&width), sizeof(uint32_t));
    stream.write(reinterpret_cast<const char*> (&height), sizeof(uint32_t));
    stream.write(reinterpret_cast<const char*> (&noEdges), sizeof(uint32_t));
    //goes through all edges in maze and prints all the data respectively
    for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        xA=(*it).xCellA;
        yA=(*it).yCellA;
        xB=(*it).xCellB;
        yB=(*it).yCellB;
        stream.write(reinterpret_cast<const char*> (&xA), sizeof(uint32_t));
        stream.write(reinterpret_cast<const char*> (&yA), sizeof(uint32_t));
        stream.write(reinterpret_cast<const char*> (&xB), sizeof(uint32_t));
        stream.write(reinterpret_cast<const char*> (&yB), sizeof(uint32_t));
    }
	return true;
}


//saving to SVG file
bool Maze::saveSVGFile(string fileName)
{
    //opening SVG files to write data into
    ofstream file(fileName);
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
    file<<"</svg>";
	return true;
}

//generate a vector of vector of Cell (2d array of Cell) 
//that will be used later on for generating maze
void Maze::generateCells()
{
    for(int i=0; i<height; i++)
    {
        vector<Cell> cells1;
        for(int j=0; j<width; j++)
        {
            Cell cell;
            cell.x = j;
            cell.y = i;
            cell.visited = false;
            cells1.push_back(cell);
        }
        cells.push_back(cells1);
    }
}

//setting all neighbours from all cells generated
void Maze::setNeighbours()
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
			//RIGHT
			if( findEdge( j, i, j+1, i) )
				cells[i][j].neighbours.push_back(&cells[i][j+1]);
			//LEFT
			if( findEdge( j, i,  j-1, i) )
				cells[i][j].neighbours.push_back(&cells[i][j-1]);
			//UP
			if( findEdge( j, i, j, i-1) )
				cells[i][j].neighbours.push_back(&cells[i-1][j]);
			//DOWN
			if( findEdge( j, i, j, i+1) )
				cells[i][j].neighbours.push_back(&cells[i+1][j]);
        }
    }
}

//setting the values of all adjacent cell
void Maze::setAdjCells()
{
	for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
			 if(cells[i][j].y != 0)
                cells[i][j].adjCell.push_back(&cells[i - 1][j]);
            if(cells[i][j].x != 0)
                cells[i][j].adjCell.push_back(&cells[i][j - 1]);
            if(cells[i][j].y != height - 1)
                cells[i][j].adjCell.push_back(&cells[i + 1][j]);
            if(cells[i][j].x != width - 1)
                cells[i][j].adjCell.push_back(&cells[i][j + 1]);
        }
    }
}

//a method to find whether there's an edge between the coordinates
bool Maze::findEdge(int xA, int yA, int xB, int yB)
{
	for(Edge e : edges)
		if( e.xCellA == xA && e.xCellB == xB
		&& e.yCellA ==yA && e.yCellB == yB)
			return true;
		else if (e.xCellA == xB && e.xCellB == xA 
		&& e.yCellA ==yB && e.yCellB == yA) 
			return true;
	return false;
}

//method to print all Edges in the maze
void Maze::printEdges(void)
{
    for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        cout<<(*it).xCellA<<" "<<(*it).yCellA<<" "
			<<(*it).xCellB<<" "<<(*it).yCellB<<"\n";
    }
}

//getter method for width
int Maze::getWidth()
{
    return width;
}

//getter method for height
int Maze::getHeight()
{
    return height;
}

//getter method for initialize
bool Maze::initialized()
{
	return initialize;
}

//setter method for initialize
void Maze::setInitialized(bool value)
{
	initialize = value;
}