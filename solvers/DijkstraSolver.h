#ifndef DjikstaSolver_H
#define DjikstraSolver_H

#include "solver.h"
#include "../data/Maze.h"
#include "../data/Cell.h"
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <utility>
#include <iterator>
#include <chrono>
#include <cmath>

//const double max_weight = numberic_limits<double>::infinity();

//typedef vector<vector<neighbor>> adj_list_t;
//typedef pair<double,Cell> weight_vertex_pair_t;


struct neighbor
{
	Cell target;
	double weight;
	neighbor(Cell arg_target,double arg_weight)
	:target(arg_target),weight(arg_weight){}
};

struct Node 
{
	Cell* cell;
	int x,y;
	double value;
	Cell* parent = nullptr ;
	vector<Node *>children;
//	Node* parent = (struct Node*) malloc(sizeof(struct Node)) ;
	Node *next = (struct Node*) malloc(sizeof(struct Node));
};

struct AdjList
{
	struct Node *head; // Pointer to head node of list
	int size; // size of the list 
};
struct MinHeap
{
	int size;
	int capacity;
	int *pos; // Decrease Key
	struct MinHeapNode **array;
};
struct MinHeapNode
{
	int x;
	int y ; 
	int v;
	int distance; 
};

class DijkstraSolver : public Solver{
protected:
	vector<vector<Cell>> visited;
	vector<vector<Cell>> calculate_value;
public:
	virtual int solve ( );
//	void alternative (Maze *,Cell,const adj_list_t,vector<double>,vector<Cell>);
	DijkstraSolver(Maze & maze, std::string name) 
		: Solver::Solver (maze, name){};
	void euclideanApply ();
	void manhattanApply ();
	void addEdge(Maze* );
	void swapMinHeapNode (struct MinHeapNode** , struct MinHeapNode**);
	int isEmpty(struct MinHeap*);
	void minHeapify(struct MinHeap* ,int );
	void decreaseKey(struct MinHeap* , Cell*  ,int );
//	MinHeapNode* extracMin(MinHeap*);

};
#endif