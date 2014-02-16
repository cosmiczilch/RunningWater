#ifndef PARTICLE_SYSTEM_DATA_H
#define PARTICLE_SYSTEM_DATA_H

#include "Libraries/glm/glm.hpp"

#include <list>
#include <string>
#include <vector>

// @Abstract
class ParticleSystemData {
public:
	virtual unsigned int   getNumParticlesToDraw() = 0;
	virtual glm::vec3*     getParticlePositionsForDrawing() = 0;
	virtual float*         getParticleSizesForDrawing() = 0;
	virtual glm::vec4*     getParticleColorsForDrawing() = 0;
	virtual std::string    getPathToTexture() = 0;

private:
};

#endif // PARTICLE_SYSTEM_DATA_H
