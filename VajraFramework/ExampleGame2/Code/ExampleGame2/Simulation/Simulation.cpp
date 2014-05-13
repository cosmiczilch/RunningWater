#include "ExampleGame2/Simulation/Grid.h"
#include "ExampleGame2/Simulation/Simulation.h"
#include "ExampleGame2/Simulation/SimulationManager.h"
#include "Vajra/Engine/Components/DerivedComponents/Renderer/ParticleSystemRenderer.h"
#include "Vajra/Engine/Core/Engine.h"
#include "Vajra/Engine/GameObject/GameObject.h"
#include "Vajra/Engine/SceneGraph/SceneGraph3D.h"

Simulation* Simulation::singleton = nullptr;

Simulation::Simulation() {
	this->init();
}

Simulation::~Simulation() {
	this->destroy();
}

Simulation* Simulation::GetInstance() {
	if (Simulation::singleton != nullptr) {
		return Simulation::singleton;
	}
	Simulation::singleton = new Simulation();
	return Simulation::singleton;
}

void Simulation::BeginSimulation() {
	ASSERT(this->simulationObject == nullptr, "Simulation not already begun");

	this->grid = new Grid();

	this->simulationObject = new GameObject(ENGINE->GetSceneGraph3D());
	ENGINE->GetSceneGraph3D()->GetRootGameObject()->AddChild(this->simulationObject->GetId());
	this->simulationManagerRef = this->simulationObject->AddComponent<SimulationManager>();
	//
	/* ParticleSystemRenderer* renderer = */ this->simulationObject->AddComponent<ParticleSystemRenderer>();
}

void Simulation::init() {
	this->grid = nullptr;
	this->simulationObject = nullptr;
}

void Simulation::destroy() {
}
