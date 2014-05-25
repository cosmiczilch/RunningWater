#ifndef GRID_H
#define GRID_H

#include "ExampleGame3/Simulation/Declarations.h"
#include "ExampleGame3/Simulation/GridHashTable.h"

#include "Libraries/Box2D/Box2D.h"
#include "Libraries/glm/glm.hpp"

class Grid {
public:
	Grid();
	~Grid();

	void Update();

private:
	void init();
	void destroy();

	void updateParticles();
	void updateInput();

	void createBox2DWorld();
	void createParticleGroup();

	b2World* boxWorld;
	b2ParticleSystemDef boxParticleSystemDef;
	b2ParticleSystem* boxParticleSystem;

	b2ParticleGroup* boxParticleGroup;

	b2Body* groundBody;
};

#endif // GRID_H
