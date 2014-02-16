#ifndef CELL_H
#define CELL_H

#include "Libraries/glm/glm.hpp"

class Cell {
public:
	glm::ivec3 center;

	float pressure;
	glm::vec3 u;

	Cell* next;
private:
};

#endif // CELL_H
