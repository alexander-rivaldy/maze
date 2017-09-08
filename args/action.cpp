#include "action.h"
#include "../generators/Generator.h"
#include "../generators/ABGenerator.h"
#include "../generators/EllerGenerator.h"
#include "../solvers/solver.h"
#include "../solvers/DFSSolver.h"
#include "../solvers/BFSSolver.h"
#include "../solvers/DijkstraSolver.h"
#include "../data/Maze.h"
#include<chrono>
/**
 * @file action.cpp contains implementations of concrete child classes of 
 * the action class which represent a request to do something from the 
 * command line.
 **/

/**
 * @param m the maze data structure to initialise and write the generated
 * maze to.
 **/
Maze&  generate_action::do_action(Maze& m)
{
	if(_ellerAlgorithm)
	{
		EllerGenerator generator(_seed, _width, _height, m);
		generator.generate();
	}
	else
	{
		ABGenerator generator(_seed, _width, _height, m);
		generator.generate();
	}
		
    
#ifdef DEBUG
    //output the adjacency lists for the maze
    //std::cerr << m;
#endif //DEBUG
    return m;
}

/**
 * perform a save action - save a maze either as a binary or svg file
 **/
Maze& save_action::do_action(Maze &m)
{
    /**
     * test if the maze has been initialized yet and if it has not 
     * throw an exception
     **/
    if(m.initialized())
    {
		
        //save a binary file
        if(_type == save_type::BINARY)
        {
			auto tStartBinary = std::chrono::high_resolution_clock::now();
            if(!m.saveBinaryFile(_name))
            {
                std::ostringstream oss;
                oss << "There was an error saving the binary file "
                    << _name << std::endl;
                throw action_failed(oss.str());
            }
			auto tEndBinary = std::chrono::high_resolution_clock::now();
		auto diffBinary =std::chrono::duration_cast<std::chrono::microseconds>(tEndBinary-tStartBinary);
		std::cout<<"Time taken to save binary : "<< diffBinary.count() << " microseconds"<<std::endl;
        }
        else
        {
			auto tStartSVG = std::chrono::high_resolution_clock::now();
            //save an svg file
            if(!m.saveSVGFile(_name))
            {
                std::ostringstream oss;
                oss << "There was an error saving the svg file " 
                    << _name << std::endl;
                throw action_failed(oss.str());
            }
			auto tEndSVG = std::chrono::high_resolution_clock::now();
		auto diffSVG =std::chrono::duration_cast<std::chrono::microseconds>(tEndSVG-tStartSVG);
		std::cout<<"Time taken to save SVG : "<< diffSVG.count() << " microseconds"<<std::endl;
        }
		
    }
    else
    {
        //the maze is not initialized
        std::ostringstream oss;
        oss << "Error: the maze is not yet initialized. " 
            << "I can't save a non-existent maze." << std::endl;
        throw action_failed(oss.str());
    }
    return m;
}

Maze & load_action::do_action(Maze & m)
{
    if(!m.loadBinaryFile(_name))
    {
        std::ostringstream oss;
        oss << "There was an error loading the binary file " 
            << _name << std::endl;
        throw action_failed(oss.str());
    }
    return m;
}

Maze & solve_action::do_action(Maze & m)
{
	if(_type == solve_type::BREADTH)
	{
		BFSSolver solver (m, _name);
		solver.solve();		
	}
	else if(_type == solve_type::DEPTH)
	{
		DFSSolver solver (m, _name);
		solver.solve();
	}
	else if(_type == solve_type::DIJKSTRA_MANHATTAN)
	{
		DijkstraSolver solver(m, _name);
		solver.solve();
	}
	else if(_type == solve_type::DIJKSTRA_EUCLIDEAN)
	{
		DijkstraSolver solver(m, _name);
		solver.manhattanApply();
		solver.solve();
	}
	return m;
}













