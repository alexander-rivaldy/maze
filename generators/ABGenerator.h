#ifndef ABGenerator_H
#define ABGenerator_H

#include "Generator.h"
#include<stdlib.h>
#include<random>
#include<vector>
#include<algorithm>
#include<time.h>
#include<chrono>
#include "../data/Maze.h"
#include "../data/Edge.h"
class ABGenerator : public Generator 
{
	public:
	ABGenerator(long& seed, int width, int height, Maze& m) 
		: Generator::Generator(seed,width,height,m){};
	bool generate();
};


#endif