#ifndef CELL_H
#define CELL_H

#include "ExampleGame2/Simulation/Declarations.h"

#include "Libraries/glm/glm.hpp"

class Cell {
public:
	Cell();
	~Cell();

	glm::ivec3 position;

	float pressure;
	glm::vec3 u;

	CellType_type cellType;
	int layer;

private:
};

#endif // CELL_H
