#ifndef Generator_H
#define Generator_H

#include<stdlib.h>
#include<random>
#include<vector>
#include<algorithm>
#include<time.h>
#include<chrono>

#include "../data/Maze.h"
#include "../data/Edge.h"
class Generator
{
    protected:
    long seed;
	Maze * maze;
	

    public:
    Generator(long&, int, int, Maze&);
    virtual bool generate()=0;
};

#endif