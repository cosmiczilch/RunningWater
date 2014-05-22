#include "ExampleGame3/Simulation/Cell.h"
#include "ExampleGame3/Simulation/Grid.h"
#include "ExampleGame3/Simulation/MarkerParticle.h"
#include "ExampleGame3/Simulation/Simulation.h"
#include "Vajra/Engine/Core/Engine.h"
#include "Vajra/Engine/DebugDrawer/DebugDrawer.h"
#include "Vajra/Engine/Timer/Timer.h"
#include "Vajra/Framework/Core/Framework.h"
#include "Vajra/Framework/Logging/Logger.h"
#include "Vajra/Utilities/Utilities.h"


glm::vec3 g = glm::vec3(0.0f, -9.8f, 0.0f);

Grid::Grid() {
	this->init();
}

Grid::~Grid() {
	this->destroy();
}

void Grid::createBox2DWorld() {
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	this->boxWorld = new b2World(gravity);

	this->boxParticleSystem = this->boxWorld->CreateParticleSystem(&(this->boxParticleSystemDef));

	this->createParticleGroup();

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = this->boxWorld->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = this->boxWorld->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


	// This is our little game loop.
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		this->boxWorld->Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

}

void Grid::createParticleGroup() {
	b2ParticleGroupDef pd;
	b2PolygonShape shape;
	shape.SetAsBox(20, 10);
	pd.shape = &shape;
	pd.flags = b2_elasticParticle;
	pd.angle = -0.5f;
	pd.angularVelocity = 2.0f;

	pd.position.Set(10 + 20, 40);
	pd.color.Set(1.0f, 1.0f, 0.0f, 1.0f);

	this->boxParticleGroup = this->boxParticleSystem->CreateParticleGroup(pd);
}

void Grid::Update() {
	float timeStep = ENGINE->GetTimer()->GetDeltaFrameTime();
	int velocityIterations = 6;
	int positionIterations = 2;
	//
	this->boxWorld->Step(timeStep, velocityIterations, positionIterations);

	this->updateParticles();
}

void Grid::updateParticles() {
	int numParticles = this->boxParticleSystem->GetParticleCount();
	// FRAMEWORK->GetLogger()->dbglog("\nNumber of particles: %d", numParticles);

	b2Vec2* positions = this->boxParticleSystem->GetPositionBuffer();
	FRAMEWORK->GetLogger()->dbglog("\nPosition: %f, %f", positions[0].x, positions[0].y);

	int index = 0;
	for (MarkerParticle* markerParticle : SIMULATION->markerParticles) {
		if (index < numParticles) {
			markerParticle->position = glm::vec3(positions[index].x * 1.0f, positions[index].y * 1.0f, 0.0f);
		} else {
			markerParticle->position = glm::vec3(-9999.0f, -9999.0f, -9999.0f);
		}
		index++;
	}
}

void Grid::init() {
	this->createBox2DWorld();
}

void Grid::destroy() {
}
