
#ifndef MAZE_H
#define MAZE_H
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include "Cell.h"
#include<vector>
#include<string>
#define MAZE_SIZE 1000

//Class structure for Maze
class Maze {
        protected:
        int width;
        int height;
        int noEdges = 0;
		bool initialize = false;
        
		
    public:
        std::vector<Edge> edges;
        std::vector<std::vector<Cell>> cells;
        bool loadBinaryFile(std::string);
        bool saveBinaryFile(std::string);
        bool saveSVGFile(std::string );
        void generateCells(void );
        void setNeighbours(void);
        void printEdges();
		bool findEdge(int , int , int , int );
		bool initialized();
        int getWidth();
        int getHeight();
        void setupData(int, int);
		void setInitialized(bool);
		void setAdjCells();
        Maze(int,int);
        Maze();
		
};

#endif
