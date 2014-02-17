#ifndef GRID_HASH_TABLE_H
#define GRID_HASH_TABLE_H

#include <complex>
#include <vector>

// Forward Declarations:
class Cell;

#define HASH_TABLE_SIZE 1000
#define HASH_TABLE_SLOT std::vector<Cell*>

class GridHashTable {
public:
	GridHashTable();
	~GridHashTable();

	Cell* AddCell    (int x, int y, int z);
	bool  HasCell    (int x, int y, int z);
	Cell* GetCell    (int x, int y, int z);
	void  RemoveCell (int x, int y, int z);

	// Iterator-like functions:
	void iterator_BeginCells();
	Cell* iterator_NextCell();

	unsigned int Size() { return this->size; }

private:
	void init();
	void destroy();

	// Utility Functions:
	static inline unsigned int hashFunction_getSlotForXYZ(int x, int y, int z);

	// Iterator private variables:
	unsigned int iterator_slotIndex;
	unsigned int iterator_slotChainIndex;
	void iterator_advanceIterators();

	unsigned int size;

	std::vector<HASH_TABLE_SLOT> slots;
};


////////////////////////////////////////////////////////////////////////////////

// Inline Functions:

unsigned int GridHashTable::hashFunction_getSlotForXYZ(int x, int y, int z) {
	return std::abs((541 * x + 79 * y + 31 * z) % HASH_TABLE_SIZE);
}

#endif // GRID_HASH_TABLE_H
