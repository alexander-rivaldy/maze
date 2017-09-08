#include "DijkstraSolver.h"
#define START_POINT 0
#define CAN_SOLVE 1
#define CANT_SOLVE -1

using namespace std;


#if 0

struct Node* newAdjListNode(int x , int y , double value)
{
	struct Node* newNode = (struct Node*) malloc (sizeof(struct Node));
	newNode->x = x;
	newNode->y = y;
	newNode->value = value;
	newNode->next = nullptr;
	return newNode;
}


struct MinHeapNode* newMinHeapNode(int x, int y,int distance)
{
	struct MinHeapNode* minHeapNode = (struct MinHeapNode*) malloc(sizeof(MinHeapNode));
	minHeapNode->x = x;
	minHeapNode->y = y; 
	minHeapNode->v = x+y;
	minHeapNode->distance = distance;
	return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
	minHeap->pos = (int *)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void DijkstraSolver::minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->distance < minHeap->array[smallest]->distance )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->distance < minHeap->array[smallest]->distance )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}

/*
 DijkstraSolver::MinHeapNode* extracMin(struct MinHeap* minHeap)
{
	if(isEmpty(minHeap))
		return NULL;

	// Store the root Node
	struct MinHeapNode* root = minHeap->array[0];

	// Replace root node with last node
	struct MinHeapNode* lastNode = minHeap->array[MinHeap->size-1];
	minHeap->array[0] = lastNode;

	// Update position of last node
	minHeap->pos[root->v] = minHeap->size-1;
	minHeap->pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;

}
*/
// Function to decreas distance value of a biven vertex v , this function use pos[] 

void DijkstraSolver::decreaseKey(struct MinHeap* minHeap, Cell* x ,int distance)
{
	// Get the index of v in heap array
	
}
struct comparator {
	bool operator() (int i , int j)
	{
		return i > j;
	}
};

int DijkstraSolver::isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size ==0;
}


void DijkstraSolver::swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* temp = *a;
	*a = *b;
	*b = temp;
}

/*
void DijkstraSolver::alternative (Maze *,Cell,const adj_list_t &list,vector<double> &min_distance,vector<Cell> &previous)
{
	int n = list.size();
	min_distance.clear();
	min_distance.resize(n,max_weight);
	min_distance[source] = 0 ;
	previous.clear();
	previous.resize(n,-1);

	priority_queue<weight_vertex_pair_t,vector<weight_vertex_pair_t>,greater<weight_vertex_pair_t>> vertex_queue;

	vertex_queue.push(make_pair(min_distance[source],source));

	while(!vertex_queue.empty())
	{
		weight_t dist = vertex_queue.top().first;

	}
}
*/
#endif 
// Main Solver for Dijkstra 
int DijkstraSolver::solve()
{
/*
* Basicly : Add + 1 value from each neighbours cells 
* and keep add it until it reach the end point
* Choose the path that has the less value in it
*/
// Variables
	//double distance_value = 10;
	//clock_t variables to record time required for the solver
	auto tStart = chrono::high_resolution_clock::now();
	visited = maze.cells; // Check Visited Cell
	vector<Cell *> pathway_queue ;
	queue<Cell*> cells_queue; // Expansion area 
	Cell * current_cell = nullptr; // Current Cell
	Cell last_cell , * neighbour_cell;

	// Initializes Cell
	visited[START_POINT][START_POINT].visited = true;
	current_cell = &visited[START_POINT][START_POINT];  
	current_cell -> visited = true;
	current_cell -> parent = nullptr;
	last_cell.x = xFinish;
	last_cell.y = yFinish;

	// Mark the current node as visited and enqueue it 
	cells_queue.push(current_cell);
	pathway_queue.push_back(current_cell);

	// While we have cells 
	while(!cells_queue.empty())
	{

		// Grab the First
		current_cell = cells_queue.front();
		cells_queue.pop();

		// Reach the last cell = Problem Solved !
		if(current_cell->x == last_cell.x && current_cell->y == last_cell.y)
		{
			// Print The PathSaver 
			vector<Cell*>real_path;
			Cell* current;
			for(unsigned int i = 0 ; i < pathway_queue.size() ; i++)
			{
				if(pathway_queue[i]->x == xFinish 
				&& pathway_queue[i]->y == yFinish)
				{
					current = pathway_queue[i];
				}

			}
			while(current->parent!=nullptr)
				{
					Edge e;// Initialize to empty again
					// Set A point 
					e.xCellA = current->x;
					e.yCellA = current->y;
					// Set B Point
					e.xCellB = current->parent->x;
					e.yCellB = current->parent->y;

					path.push_back(e);
					real_path.push_back(current->parent);
					current = current->parent;
				}
				
			//calculating time taken to solve maze
			auto tEnd = chrono::high_resolution_clock::now();
			auto diff =chrono::duration_cast<chrono::microseconds>(tEnd-tStart);
			cout<<"Time taken to solve : "<< diff.count() 
				<< " microseconds"<<endl;
			
			
			tStart = chrono::high_resolution_clock::now();
			drawPath(); // Path is vector<Edges>
				//calculating time taken to draw SVG
			tEnd = chrono::high_resolution_clock::now();
			diff =chrono::duration_cast<chrono::microseconds>(tEnd-tStart);
			cout<<"Time taken to draw SVG : "<< diff.count() 
				<< " microseconds"<<endl;
			
		return CAN_SOLVE;
		}
		else
		{
			// Find Unvisited Neighbour
			for(auto i = current_cell->neighbours.begin();
				i<current_cell->neighbours.end(); i++)
			{
				neighbour_cell = *i;
				if(neighbour_cell->visited == false)
				{
					neighbour_cell->visited = true ; // Mark it as visited 
					neighbour_cell->parent = current_cell;
					neighbour_cell->value += current_cell->value;
				//	cout << "Neighbour Cell Value is Now : " << neighbour_cell->value << endl;
				//	neighbour_cell->value = current_cell->value + distance_value;
					cells_queue.push(neighbour_cell);
					pathway_queue.push_back(neighbour_cell);
				}
			}
		}

	}

	return CANT_SOLVE;
 
}


void DijkstraSolver::manhattanApply()
{
	int canSolve = -1;
	calculate_value = maze.cells; 
	for(unsigned int i = 0 ; i < calculate_value.size();i++)
	{
		for(unsigned int j = 0 ; j <calculate_value[i].size();j++)
		{
			auto&current = calculate_value[i][j];
			maze.cells[i][j].value = (xFinish-current.x)+(yFinish-current.y);
			//cout << "Manhattan Current : " << maze.cells[i][j].value << endl;
		}
	}

	canSolve = solve();

	if(canSolve == CAN_SOLVE)
	{
		//cout << "System : This Maze Can Solve " << endl;
	}
	else
	{
		//cout << "System : This Maze Cannot Solve " << endl;
	}
	
}

void DijkstraSolver::euclideanApply()
{
	int canSolve = -1;
	calculate_value = maze.cells; 
	for(unsigned int i = 0 ; i < calculate_value.size();i++)
	{
		for(unsigned int j = 0 ; j <calculate_value[i].size();j++)
		{
			auto&current = calculate_value[i][j];
			maze.cells[i][j].value = sqrt(pow((xFinish-current.x),2.0)
				+ pow((yFinish-current.y),2.0));
			//cout << "Euclidean Current : " << maze.cells[i][j].value << endl;
		}
	}

	canSolve = solve();

	if(canSolve == CAN_SOLVE)
	{
		//cout << "Can Solve :3 " << endl;
	}
	else
	{
		//cout << "Cannot Solve ._. " << endl;
	}


}