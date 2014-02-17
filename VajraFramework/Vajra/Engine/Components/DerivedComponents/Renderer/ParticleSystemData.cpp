#include "Vajra/Engine/Components/DerivedComponents/Renderer/ParticleSystemData.h"

unsigned int ParticleSystemData::componentTypeId = COMPONENT_TYPE_ID_PARTICLE_SYSTEM_DATA;

ParticleSystemData::ParticleSystemData() : Component() {
	this->init();
}

ParticleSystemData::ParticleSystemData(Object* object_) : Component(object_) {
	this->init();
}

ParticleSystemData::~ParticleSystemData() {
	this->destroy();
}

void ParticleSystemData::HandleMessage(MessageChunk messageChunk) {
	Component::HandleMessage(messageChunk);
}

void ParticleSystemData::init() {
}

void ParticleSystemData::destroy() {
}
