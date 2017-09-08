#include "Generator.h"


using namespace std;

//constructor that takes seed value as parameter
Generator::Generator(long& seedValue, int width, int height, Maze & m)
{
    seed = seedValue;
	maze = &m;
	maze->setupData(width,height);
}
