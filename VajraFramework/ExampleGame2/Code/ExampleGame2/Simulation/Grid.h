#ifndef GRID_H
#define GRID_H

#include "ExampleGame2/Simulation/Declarations.h"
#include "ExampleGame2/Simulation/GridHashTable.h"

#include "Libraries/glm/glm.hpp"

// Forward Declarations:
class Cell;

class Grid {
public:
	Grid();
	~Grid();

	void Update();

private:
	void init();
	void destroy();

	void markSolidCells();

	void updateCells();
	void drawCells();

	// Utility Functions:
	void positionToGridCellCoords(glm::vec3 position, int& out_x, int& out_y, int& out_z);

	GridHashTable* hashTable;
};

#endif // GRID_H
