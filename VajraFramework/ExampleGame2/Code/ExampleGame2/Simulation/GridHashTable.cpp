#include "ExampleGame2/Simulation/Cell.h"
#include "ExampleGame2/Simulation/GridHashTable.h"

GridHashTable::GridHashTable() {
	this->init();
}

GridHashTable::~GridHashTable() {
	this->destroy();
}

void GridHashTable::AddCell(Cell* cell) {
	unsigned int slotIndex = GridHashTable::hashFunction_getSlotForXYZ(cell->center.x, cell->center.y, cell->center.z);
	this->slots[slotIndex].push_back(cell);
}

Cell* GridHashTable::GetCell(int x, int y, int z) {
	unsigned int slotIndex = GridHashTable::hashFunction_getSlotForXYZ(x, y, z);
	if (!this->slots[slotIndex].empty()) {
		for (Cell* cell : this->slots[slotIndex]) {
			if (cell->center.x == x && cell->center.y == y && cell->center.z == z) {
				return cell;
			}
		}
	}
	return nullptr;
}

bool GridHashTable::HasCell(int x, int y, int z) {
	return (this->GetCell(x, y, z) != nullptr);
}

void GridHashTable::init() {
	this->slots.resize(HASH_TABLE_SIZE);
}

void GridHashTable::destroy() {
}
