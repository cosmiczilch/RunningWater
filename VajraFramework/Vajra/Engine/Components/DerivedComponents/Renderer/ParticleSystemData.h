#ifndef PARTICLE_SYSTEM_DATA_H
#define PARTICLE_SYSTEM_DATA_H

#include "Vajra/Common/Components/Component.h"

#include "Libraries/glm/glm.hpp"

#include <list>
#include <string>
#include <vector>

// @Abstract
class ParticleSystemData : public Component {
public:
	ParticleSystemData();
	ParticleSystemData(Object* object_);
	~ParticleSystemData();

	static inline unsigned int GetTypeId() { return componentTypeId; }

	// @Override
	virtual void HandleMessage(MessageChunk messageChunk);

	virtual unsigned int   getNumParticlesToDraw() = 0;
	virtual glm::vec3*     getParticlePositionsForDrawing() = 0;
	virtual float*         getParticleSizesForDrawing() = 0;
	virtual glm::vec4*     getParticleColorsForDrawing() = 0;
	virtual std::string    getPathToTexture() = 0;

private:
	void init();
	void destroy();

	static unsigned int componentTypeId;
};

#endif // PARTICLE_SYSTEM_DATA_H
