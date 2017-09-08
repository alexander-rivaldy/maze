#include <iostream>
#include <exception>
#include <sstream>
#include "../constants/constants.h"
#include <chrono>
#pragma once
/** 
 * forwards declaration required to avoid a recursive include
 **/
class Maze;
/**
 * abstract class that represents all types of actions that can
 * be requested from the command line.
 **/
class action
{
    public:
        /**
         * pure virtual function that must be implemented in each
         * child class to describe how to perform the action 
         * specified on a maze.
         * @return a reference to the maze passed in.
         **/
        virtual Maze & 
            do_action(Maze &) = 0;
};

/**
 * exception that may be thrown from any do_action() function to
 * indicate that that action failed.
 **/
class action_failed : public std::exception
{
    /**
     * message to be returned from this exception
     **/
    std::string _message;

    public:
    /**
     * constructor - simply assigns the message
     **/
    action_failed(const std::string message) 
        : _message(message) {}

    /**
     * return the message to be displayed. After this, 
     * the message is no longer valid in this class as it is
     * returned by move.
     **/
    const char * what(void)
    {
        return std::move(_message.c_str());
    }

};

/**
 * represents a request to generate a maze
 **/
class generate_action : public action
{
    /**
     *  the seed used to start the random number generator or 
     *  @ref constants::ERROR if it has not been
     *  initialized yet.
     **/
    long _seed;

    /**
     * the width of the maze to generate
     **/
    unsigned _width;

    /**
     * the height of the maze to generate
     **/
    unsigned _height;
	/**
	 * type of the generation algorithm
	 **/
	bool _ellerAlgorithm;

    public: 

    /**
     * default constructor - required to insert actions into an
     * stl container.
     **/
    generate_action(void){}

    /**
     * creates a generate_action based on the seed, width and 
     * height being specified
     **/
    generate_action(long seed, unsigned width, unsigned height, bool ellerAlgorithm)
        : _seed(
                seed == ERROR ? 
                std::chrono::duration_cast<
                std::chrono::milliseconds>(
                    std::chrono::system_clock::now()
                    .time_since_epoch()).count() 
                : seed), 
        _width(width), _height(height) , _ellerAlgorithm(ellerAlgorithm)
        {
#ifdef DEBUG
            std::cerr << "seed: " << _seed << std::endl;
#endif
        }

    virtual Maze & do_action(Maze &);
};

/**
 * defines a load action specified from the command line
 **/
class load_action : public action
{
    /**
     * the file name of the file to load from disk
     **/
    std::string _name;
    public:
    /**
     * constructor - just assigns the file name; the rest of the 
     * work will be done later.
     **/
    load_action(const std::string & name) : _name(name)
    {
    }

    virtual Maze& do_action(Maze &);

};

/**
 * how do we want to save a file? Binary or Svg? 
 **/
enum class save_type
{
    ///save the file as binary
    BINARY, 
    ///save the file as svg
    SVG
};

/**
 * models a save request passed in from the command line
 **/
class save_action : public action
{
    /**
     * the type of saving to be done
     **/
    save_type _type;

    /**
     * the name of the file to save to
     **/
    std::string _name;

    public:
    /**
     * constructor - simply assigns the type of save and the 
     * file to save to
     **/
    save_action(save_type type, const std::string & name) 
        : _type(type), _name(name)
    {
    }
    virtual Maze & do_action(Maze &);
};


//how do we want to solve the maze
enum class solve_type
{
	//solve with breadth first search
	BREADTH,
	//solve with depth first search
	DEPTH,
	//solve with djikstra algorithm, manhattan 
	DIJKSTRA_MANHATTAN,
	//solve with djikstra algorithm, euclidean 
	DIJKSTRA_EUCLIDEAN
};

class solve_action : public action
{
    /**
     * the type of saving to be done
     **/
    solve_type _type;

    /**
     * the name of the file to save to
     **/
    std::string _name;

    public:
    /**
     * constructor - simply assigns the type of save and the 
     * file to save to
     **/
    solve_action(solve_type type, const std::string & name) 
        : _type(type), _name(name)
    {
    }
    virtual Maze & do_action(Maze &);
};



