//
//  GridZone.h
//  Created by Matt Kaufmann on 01/07/14.
//

#ifndef GRIDZONE_H
#define GRIDZONE_H

#include "Vajra/Common/Components/Component.h"

class GridZone : public Component {
public:
	GridZone();
	GridZone(Object* object_);
	~GridZone();

	static inline ComponentIdType GetTypeId() { return componentTypeId; };

	void SetZoneBounds(int xMin, int zMin, int xMax, int zMax);

	unsigned int CollisionCheck(GridCell* startCell, GridCell* destCell);

protected:

private:
	void init();
	void destroy();

	int westBound;
	int eastBound;
	int southBound;
	int northBound;

	static unsigned int componentTypeId;
};

#endif // GRIDZONE_H
