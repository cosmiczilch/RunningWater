#ifndef GRID_H
#define GRID_H

#include "ExampleGame2/Simulation/Declarations.h"
#include "ExampleGame2/Simulation/GridHashTable.h"

// Forward Declarations:
class Cell;

class Grid {
public:
	Grid();
	~Grid();

private:
	void init();
	void destroy();

	GridHashTable* hashTable;
};

#endif // GRID_H
