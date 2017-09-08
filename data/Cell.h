#ifndef CELL_H
#define CELL_H

#include "Edge.h"
#include<vector>
#define MAX_NEIGHBOUR 4

//struct for cell, contains coordinate, visited value (for generating maze) 
//and references to its neighbours (max 4 neighbours)
typedef struct Cell {
    int x;
    int y;
    bool visited = false;
	double value = 0 ;
    std::vector<Cell*> neighbours;
    std::vector<Cell*> adjCell;
	Cell* parent;
	Cell* south=NULL;
}Cell;

#endif