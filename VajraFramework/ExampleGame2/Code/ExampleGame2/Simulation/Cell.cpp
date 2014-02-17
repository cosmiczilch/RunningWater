#include "ExampleGame2/Simulation/Cell.h"

Cell::Cell() {
	this->pressure = 0.0f;
	this->u        = glm::vec3(0.0f, 0.0f, 0.0f);
	this->cellType = CELL_TYPE_UNSPECIFIED;
	this->layer    = -1;
}

Cell::~Cell() {
}
