#include "ExampleGame3/Components/ComponentTypes/ComponentTypeIds.h"
#include "ExampleGame3/Simulation/Declarations.h"
#include "ExampleGame3/Simulation/Grid.h"
#include "ExampleGame3/Simulation/MarkerParticle.h"
#include "ExampleGame3/Simulation/Simulation.h"
#include "ExampleGame3/Simulation/SimulationManager.h"
#include "Vajra/Engine/MessageHub/MessageHub.h"
#include "Vajra/Common/Messages/Message.h"
#include "Vajra/Engine/Core/Engine.h"
#include "Vajra/Engine/GameObject/GameObject.h"
#include "Vajra/Framework/Core/Framework.h"
#include "Vajra/Framework/DeviceUtils/FileSystemUtils/FileSystemUtils.h"
#include "Vajra/Framework/Logging/Logger.h"
#include "Vajra/Utilities/MathUtilities.h"

SimulationManager::SimulationManager() : ParticleSystemData() {
	this->init();
}

SimulationManager::SimulationManager(Object* object_) : ParticleSystemData(object_) {
	this->init();
}

SimulationManager::~SimulationManager() {
	this->destroy();
}

void SimulationManager::HandleMessage(MessageChunk messageChunk) {
	ParticleSystemData::HandleMessage(messageChunk);
}

void SimulationManager::start() {
	// Create the marker particles:
	this->createMarkerParticles();
}

const float g_initialCubeSize = INITIAL_WATER_CUBE_SIZE;

void SimulationManager::update() {
	// FRAMEWORK->GetLogger()->dbglog("\nHere in SimulationManager update()");

	SIMULATION->grid->Update();

#if 0
	for (MarkerParticle* markerParticle : SIMULATION->markerParticles) {
		markerParticle->position = glm::vec3(randf() * g_initialCubeSize, randf() * g_initialCubeSize, randf() * g_initialCubeSize);
	}
#endif

	this->updateShaderAttributeVectors();
}

void SimulationManager::end() {
}

void SimulationManager::createMarkerParticles() {
	ASSERT(SIMULATION->markerParticles.size() == 0, "No particles have been created already");
	for (unsigned int i = 0; i < NUMBER_OF_MARKER_PARTICLES; ++i) {
		MarkerParticle* markerParticle = new MarkerParticle();
		// markerParticle->position = glm::vec3(randf() * g_initialCubeSize, 2.0f + randf() * g_initialCubeSize, randf() * g_initialCubeSize);
		markerParticle->position = glm::vec3(-9999.0f, -9999.0f, -9999.0f);

		SIMULATION->markerParticles.push_back(markerParticle);
	}

	this->initShaderAttributeVectors();
}

void SimulationManager::initShaderAttributeVectors() {
	this->numParticlesToDraw = NUMBER_OF_MARKER_PARTICLES;

	this->particlePositions = new glm::vec3[NUMBER_OF_MARKER_PARTICLES];
	this->particleSizes     = new float[NUMBER_OF_MARKER_PARTICLES];
	this->particleColors    = new glm::vec4[NUMBER_OF_MARKER_PARTICLES];

	for (unsigned int i = 0; i < this->numParticlesToDraw; ++i) {
		this->particlePositions[i] = glm::vec3(0.0f, 0.0f, 0.0f);
		this->particleSizes[i]     = 0.0f;
		this->particleColors[i]    = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	ENGINE->GetMessageHub()->SendPointcastMessage(MESSAGE_TYPE_PARTICLE_SYSTEM_INITED, this->GetObject()->GetId(), this->GetObject()->GetId());

	this->updateShaderAttributeVectors();
}

void SimulationManager::updateShaderAttributeVectors() {
	// Copy the updated positions of all the marker particles:
	unsigned int particleIdx = 0;
	for (MarkerParticle* particle : SIMULATION->markerParticles) {
		// Copy the particles in reverse order for transperancy reasons:
		this->particlePositions[this->numParticlesToDraw - particleIdx - 1] = particle->position;
		// TODO [Implement] Implement particle sizes and colors:
		this->particleSizes[this->numParticlesToDraw - particleIdx - 1]     = 5;
		this->particleColors[this->numParticlesToDraw - particleIdx - 1]    = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		++particleIdx;
	}

	// Reset the rest:
	for (unsigned int i = particleIdx; i < NUMBER_OF_MARKER_PARTICLES; ++i) {
		this->particlePositions[this->numParticlesToDraw - i - 1] = glm::vec3(0.0f, 0.0f, 0.0f);
		this->particleSizes[this->numParticlesToDraw - i - 1]     = 0.0f;
		this->particleColors[this->numParticlesToDraw - i - 1]    = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	ENGINE->GetMessageHub()->SendPointcastMessage(MESSAGE_TYPE_PARTICLE_SYSTEM_UPDATED, this->GetObject()->GetId(), this->GetObject()->GetId());
}

void SimulationManager::init() {
	this->addSubscriptionToMessageType(MESSAGE_TYPE_FRAME_EVENT, this->GetTypeId(), false);

	this->particlePositions = nullptr;
	this->particleColors    = nullptr;
	this->particleSizes     = nullptr;
	this->numParticlesToDraw = 0;
	//
	this->pathToTexture = FRAMEWORK->GetFileSystemUtils()->GetDevicePictureResourcesFolderName() + "yellow.png";

	// TODO [Hack] Remove this when scene start messages are sent:
	this->start();
}

void SimulationManager::destroy() {
	this->removeSubscriptionToAllMessageTypes(this->GetTypeId());

	// TODO [Hack] Remove this when scene end messages are sent:
	this->end();
}

