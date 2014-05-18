#ifndef SIMULATION_MANAGER_H
#define SIMULATION_MANAGER_H

#include "Vajra/Common/Components/Component.h"
#include "Vajra/Engine/Components/DerivedComponents/Renderer/ParticleSystemData.h"

//[[COMPONENT]]//
class SimulationManager : public ParticleSystemData {
public:
	SimulationManager();
	SimulationManager(Object* object_);
	~SimulationManager();

	static inline unsigned int GetTypeId() { return ParticleSystemData::GetTypeId(); }

	// @Override
	virtual void HandleMessage(MessageChunk messageChunk);

	// @Override
	virtual void start();
	virtual void update();
	virtual void end();

	// Functions required to expose the particle attribute vectors for drawing:
	// @Override
	virtual unsigned int   getNumParticlesToDraw()           { return this->numParticlesToDraw; }
	virtual glm::vec3*     getParticlePositionsForDrawing()  { return this->particlePositions;  }
	virtual float*         getParticleSizesForDrawing()      { return this->particleSizes;  }
	virtual glm::vec4*     getParticleColorsForDrawing()     { return this->particleColors;  }
	virtual std::string    getPathToTexture()                { return this->pathToTexture; }

private:
	void init();
	void destroy();

	void createMarkerParticles();

	void initShaderAttributeVectors();
	void updateShaderAttributeVectors();

	// Shader attribute vectors for drawing:
	unsigned int numParticlesToDraw;
	glm::vec3* particlePositions;
	float* particleSizes;
	glm::vec4* particleColors;
	//
	std::string pathToTexture;
};

#endif // SIMULATION_MANAGER_H
