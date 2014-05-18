#ifndef GRID_H
#define GRID_H

#include "ExampleGame2/Simulation/Declarations.h"
#include "ExampleGame2/Simulation/GridHashTable.h"

#include "Libraries/glm/glm.hpp"

// Forward Declarations:
class Cell;

enum NEIGHBOR_type {
	NEIGHBOR_BELOW = 0,
	NEIGHBOR_ABOVE,
	NEIGHBOR_LEFT,
	NEIGHBOR_RIGHT,
	NEIGHBOR_BEHIND,
	NEIGHBOR_FRONT,
	//
	NEIGHBOR_NUM_NEIGHBORS,
};

class Grid {
public:
	Grid();
	~Grid();

	void Update();

private:
	void init();
	void destroy();

	bool isCellSolid(int x, int y, int z);

	void updateCells();
	void updateConvection();
	void updateExternalForces();
	void updateSolidNormalForces();
	void updateSolidCellVelocities();
	void extrapolateFluidVelocitiesToAirCells();
	void applyVelocities();
	void drawCells();

	Cell* getNeighborForCell(Cell* cell, NEIGHBOR_type neighborType, bool create = true);

	// Utility Functions:
	void positionToGridCellCoords(glm::vec3 position, int& out_x, int& out_y, int& out_z);

	GridHashTable* hashTable;
};

#endif // GRID_H
