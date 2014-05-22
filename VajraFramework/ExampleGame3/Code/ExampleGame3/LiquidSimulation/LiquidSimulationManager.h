#ifndef LIQUID_SIMULATION_MANAGER_H
#define LIQUID_SIMULATION_MANAGER_H

#include "Libraries/Box2D/Box2D.h"

class LiquidSimulationManager {
public:
	LiquidSimulationManager();
	~LiquidSimulationManager();

private:
	void init();
	void destroy();

};

#endif // LIQUID_SIMULATION_MANAGER_H
