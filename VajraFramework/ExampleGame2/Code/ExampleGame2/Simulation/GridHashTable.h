#ifndef GRID_HASH_TABLE_H
#define GRID_HASH_TABLE_H

#include <vector>

// Forward Declarations:
class Cell;

#define HASH_TABLE_SIZE 1000
#define HASH_TABLE_SLOT std::vector<Cell*>

class GridHashTable {
public:
	GridHashTable();
	~GridHashTable();

	void  AddCell(Cell* cell);
	bool  HasCell(int x, int y, int z);
	Cell* GetCell(int x, int y, int z);

private:
	void init();
	void destroy();

	// Utility Functions:
	static inline unsigned int hashFunction_getSlotForXYZ(int x, int y, int z);

	std::vector<HASH_TABLE_SLOT> slots;
};

////////////////////////////////////////////////////////////////////////////////

// Inline Functions:

unsigned int GridHashTable::hashFunction_getSlotForXYZ(int x, int y, int z) {
	return std::abs((541 * x + 79 * y + 31 * z) % HASH_TABLE_SIZE);
}

#endif // GRID_HASH_TABLE_H
