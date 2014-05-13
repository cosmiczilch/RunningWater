#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

// Forward Declarations:
class GameObject;
class Grid;
class MarkerParticle;
class SimulationManager;

class Simulation {
public:
	~Simulation();

	static Simulation* GetInstance();

	void BeginSimulation();

	GameObject* GetSimulationObject() { return this->simulationObject; }

private:
	// Make this a singleton:
	Simulation();

	static Simulation* singleton;

	Grid* grid;
	std::vector<MarkerParticle*> markerParticles;
	//
	// A game object on which the SimulationManager and Renderer components will be added:
	GameObject* simulationObject;
	SimulationManager* simulationManagerRef;

	void init();
	void destroy();

	friend class SimulationManager;
	friend class Grid;
};

#define SIMULATION Simulation::GetInstance()

#endif // SIMULATION_H
