#include "ExampleGame3/Simulation/Cell.h"
#include "ExampleGame3/Simulation/GridHashTable.h"
#include "Vajra/Utilities/Utilities.h"

GridHashTable::GridHashTable() {
	this->init();
}

GridHashTable::~GridHashTable() {
	this->destroy();
}

Cell* GridHashTable::AddCell(int x, int y, int z) {
	Cell* cell = new Cell();
	cell->position.x = x;
	cell->position.y = y;
	cell->position.z = z;

	unsigned int slotIndex = GridHashTable::hashFunction_getSlotForXYZ(x, y, z);
	this->slots[slotIndex].push_back(cell);

	this->size++;

	return cell;
}

Cell* GridHashTable::GetCell(int x, int y, int z) {
	unsigned int slotIndex = GridHashTable::hashFunction_getSlotForXYZ(x, y, z);
	if (!this->slots[slotIndex].empty()) {
		for (Cell* cell : this->slots[slotIndex]) {
			if (cell->position.x == x && cell->position.y == y && cell->position.z == z) {
				return cell;
			}
		}
	}
	return nullptr;
}

bool GridHashTable::HasCell(int x, int y, int z) {
	return (this->GetCell(x, y, z) != nullptr);
}

void GridHashTable::RemoveCell(int x, int y, int z) {
	ASSERT(this->HasCell(x, y, z), "Cell at %d, %d, %d exists", x, y, z);

	unsigned int slotIndex = GridHashTable::hashFunction_getSlotForXYZ(x, y, z);
	for (auto it = this->slots[slotIndex].begin(); it != this->slots[slotIndex].end(); ++it) {
		Cell* cell = *it;
		if (cell->position.x == x && cell->position.y == y && cell->position.z == z) {
			this->slots[slotIndex].erase(it);
			this->size--;
			delete cell;
			break;
		}
	}
}

void GridHashTable::init() {
	this->size = 0;

	this->iterator_slotIndex      = 0;
	this->iterator_slotChainIndex = 0;

	this->slots.resize(HASH_TABLE_SIZE);
}

void GridHashTable::destroy() {
}

void GridHashTable::iterator_BeginCells() {
	this->iterator_slotIndex      = 0;
	this->iterator_slotChainIndex = 0;

	// Advance iterators to first occupied cell:
	while (this->iterator_slotIndex < this->slots.size() &&
		this->slots[this->iterator_slotIndex].size() == 0) {
		this->iterator_slotIndex++;
	}
}

Cell* GridHashTable::iterator_NextCell() {
	Cell* returnCell = nullptr;

	if (this->iterator_slotIndex < this->slots.size()) {
		if (this->slots[this->iterator_slotIndex].size() > this->iterator_slotChainIndex) {
			returnCell = this->slots[this->iterator_slotIndex][this->iterator_slotChainIndex];
		}

		// Advance iterators:
		if (this->slots[this->iterator_slotIndex].size() > (this->iterator_slotChainIndex + 1)) {
			this->iterator_slotChainIndex++;
		} else {
			this->iterator_slotChainIndex = 0;
			this->iterator_slotIndex++;
			while (this->iterator_slotIndex < this->slots.size() &&
			   	this->slots[this->iterator_slotIndex].size() == 0) {
				this->iterator_slotIndex++;
			}
		}
	}

	return returnCell;
}

void GridHashTable::iterator_advanceIterators() {
}
