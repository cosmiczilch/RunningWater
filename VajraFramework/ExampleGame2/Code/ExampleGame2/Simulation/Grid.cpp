#include "ExampleGame2/Simulation/Cell.h"
#include "ExampleGame2/Simulation/Grid.h"

Grid::Grid() {
	this->init();
}

Grid::~Grid() {
	this->destroy();
}

void Grid::init() {
	this->hashTable = new GridHashTable();
}

void Grid::destroy() {
}
