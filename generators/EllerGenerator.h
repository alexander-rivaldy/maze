#ifndef EllerGenerator_H
#define EllerGenerator_H

#include "Generator.h"
#include<stdlib.h>
#include<random>
#include<vector>
#include<algorithm>
#include<time.h>
#include<chrono>
#include "../data/Maze.h"
#include "../data/Edge.h"
class EllerGenerator : public Generator 
{
	
	public:
		EllerGenerator(long& seed, int width, int height, Maze& m) 
			: Generator::Generator(seed,width,height,m){};
		int checkVertical(std::vector<Cell*>, int); 
		int findSetNumber(std::vector<std::vector<Cell*>>, int, int);
		bool generate();
};

#endif