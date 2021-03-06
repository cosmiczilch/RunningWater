#include "ExampleGame3/ComponentMapper/ComponentMapper.h"
#include "Vajra/Utilities/StringUtilities.h"

#include "Vajra/Engine/Components/DerivedComponents/Animation/RigidAnimation/RigidAnimation.h"
#include "Vajra/Engine/Components/DerivedComponents/Animation/BakedSkeletalAnimation/BakedSkeletalAnimation.h"
#include "Vajra/Engine/Components/DerivedComponents/Camera/Camera.h"
#include "Vajra/Engine/Components/DerivedComponents/Lights/DirectionalLight/DirectionalLight.h"
#include "Vajra/Engine/Components/DerivedComponents/Renderer/ParticleSystemRenderer.h"
#include "Vajra/Engine/Components/DerivedComponents/Renderer/MeshRenderer.h"
#include "Vajra/Engine/Components/DerivedComponents/Audio/AudioSource.h"
#include "Vajra/Engine/Components/DerivedComponents/Armature/Armature.h"
#include "Vajra/Engine/Components/DerivedComponents/Transform/Transform.h"
#include "Vajra/Engine/ParticleSystems/ParticleSystem.h"
#include "ExampleGame3/Components/GameScripts/SampleGameScript.h"


Component* ComponentMapper::AddNewComponentToGameObjectByComponentName(GameObject* gameObject, std::string componentName) {

	
	if (componentName == "RigidAnimation") {
		RigidAnimation* component = gameObject->GetComponent<RigidAnimation>();
		if (component == nullptr) { component = gameObject->AddComponent<RigidAnimation>(); }
		return component;
	}
	
	if (componentName == "BakedSkeletalAnimation") {
		BakedSkeletalAnimation* component = gameObject->GetComponent<BakedSkeletalAnimation>();
		if (component == nullptr) { component = gameObject->AddComponent<BakedSkeletalAnimation>(); }
		return component;
	}
	
	if (componentName == "Camera") {
		Camera* component = gameObject->GetComponent<Camera>();
		if (component == nullptr) { component = gameObject->AddComponent<Camera>(); }
		return component;
	}
	
	if (componentName == "DirectionalLight") {
		DirectionalLight* component = gameObject->GetComponent<DirectionalLight>();
		if (component == nullptr) { component = gameObject->AddComponent<DirectionalLight>(); }
		return component;
	}
	
	if (componentName == "ParticleSystemRenderer") {
		ParticleSystemRenderer* component = gameObject->GetComponent<ParticleSystemRenderer>();
		if (component == nullptr) { component = gameObject->AddComponent<ParticleSystemRenderer>(); }
		return component;
	}
	
	if (componentName == "MeshRenderer") {
		MeshRenderer* component = gameObject->GetComponent<MeshRenderer>();
		if (component == nullptr) { component = gameObject->AddComponent<MeshRenderer>(); }
		return component;
	}
	
	if (componentName == "AudioSource") {
		AudioSource* component = gameObject->GetComponent<AudioSource>();
		if (component == nullptr) { component = gameObject->AddComponent<AudioSource>(); }
		return component;
	}
	
	if (componentName == "Armature") {
		Armature* component = gameObject->GetComponent<Armature>();
		if (component == nullptr) { component = gameObject->AddComponent<Armature>(); }
		return component;
	}
	
	if (componentName == "Transform") {
		Transform* component = gameObject->GetComponent<Transform>();
		if (component == nullptr) { component = gameObject->AddComponent<Transform>(); }
		return component;
	}
	
	if (componentName == "ParticleSystem") {
		ParticleSystem* component = gameObject->GetComponent<ParticleSystem>();
		if (component == nullptr) { component = gameObject->AddComponent<ParticleSystem>(); }
		return component;
	}
	
	if (componentName == "SampleGameScript") {
		SampleGameScript* component = gameObject->GetComponent<SampleGameScript>();
		if (component == nullptr) { component = gameObject->AddComponent<SampleGameScript>(); }
		return component;
	}

	return nullptr;
}


void ComponentMapper::InitializePropertyByComponentAndPropertyNames(GameObject *gameObject, std::string componentName, std::string propertyName, std::vector<std::string> argv) {

	
	if (componentName == "RigidAnimation") {
		RigidAnimation* component = gameObject->GetComponent<RigidAnimation>();
		if (component == nullptr) { return; }
		if (propertyName == "AddAnimationClip") {
			if ((int)argv.size() < 1) { return; }
			component->AddAnimationClip(ConvertStringToString(argv[0]));
			return;
		}
		if (propertyName == "PlayAnimationClip") {
			if ((int)argv.size() < 1) { return; }
			component->PlayAnimationClip(ConvertStringToString(argv[0]));
			return;
		}
		return;
	}
	
	if (componentName == "BakedSkeletalAnimation") {
		BakedSkeletalAnimation* component = gameObject->GetComponent<BakedSkeletalAnimation>();
		if (component == nullptr) { return; }
		if (propertyName == "AddAnimationClip") {
			if ((int)argv.size() < 2) { return; }
			component->AddAnimationClip(ConvertStringToString(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]));
			return;
		}
		if (propertyName == "PlayAnimationClip") {
			if ((int)argv.size() < 1) { return; }
			component->PlayAnimationClip(ConvertStringToString(argv[0]));
			return;
		}
		return;
	}
	
	if (componentName == "Camera") {
		Camera* component = gameObject->GetComponent<Camera>();
		if (component == nullptr) { return; }
		if (propertyName == "SetCameraType") {
			if ((int)argv.size() < 1) { return; }
			component->SetCameraType(StringUtilities::ConvertStringToInt(argv[0]));
			return;
		}
		if (propertyName == "SetFOV") {
			if ((int)argv.size() < 1) { return; }
			component->SetFOV(StringUtilities::ConvertStringToFloat(argv[0]));
			return;
		}
		return;
	}
	
	if (componentName == "DirectionalLight") {
		DirectionalLight* component = gameObject->GetComponent<DirectionalLight>();
		if (component == nullptr) { return; }
		if (propertyName == "SetAmbientColor") {
			if ((int)argv.size() < 4) { return; }
			component->SetAmbientColor(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]), StringUtilities::ConvertStringToFloat(argv[3]));
			return;
		}
		if (propertyName == "SetDiffuseColor") {
			if ((int)argv.size() < 4) { return; }
			component->SetDiffuseColor(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]), StringUtilities::ConvertStringToFloat(argv[3]));
			return;
		}
		if (propertyName == "SetSpecularColor") {
			if ((int)argv.size() < 4) { return; }
			component->SetSpecularColor(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]), StringUtilities::ConvertStringToFloat(argv[3]));
			return;
		}
		return;
	}
	
	if (componentName == "ParticleSystemRenderer") {
		ParticleSystemRenderer* component = gameObject->GetComponent<ParticleSystemRenderer>();
		if (component == nullptr) { return; }
		return;
	}
	
	if (componentName == "MeshRenderer") {
		MeshRenderer* component = gameObject->GetComponent<MeshRenderer>();
		if (component == nullptr) { return; }
		if (propertyName == "InitMesh") {
			if ((int)argv.size() < 1) { return; }
			component->InitMesh(ConvertStringToString(argv[0]));
			return;
		}
		return;
	}
	
	if (componentName == "AudioSource") {
		AudioSource* component = gameObject->GetComponent<AudioSource>();
		if (component == nullptr) { return; }
		if (propertyName == "SetAudioClip") {
			if ((int)argv.size() < 1) { return; }
			component->SetAudioClip(ConvertStringToString(argv[0]));
			return;
		}
		if (propertyName == "SetVolume") {
			if ((int)argv.size() < 1) { return; }
			component->SetVolume(StringUtilities::ConvertStringToFloat(argv[0]));
			return;
		}
		if (propertyName == "SetPlaybackSpeed") {
			if ((int)argv.size() < 1) { return; }
			component->SetPlaybackSpeed(StringUtilities::ConvertStringToFloat(argv[0]));
			return;
		}
		return;
	}
	
	if (componentName == "Armature") {
		Armature* component = gameObject->GetComponent<Armature>();
		if (component == nullptr) { return; }
		if (propertyName == "InitArmature") {
			if ((int)argv.size() < 1) { return; }
			component->InitArmature(ConvertStringToString(argv[0]));
			return;
		}
		return;
	}
	
	if (componentName == "Transform") {
		Transform* component = gameObject->GetComponent<Transform>();
		if (component == nullptr) { return; }
		if (propertyName == "SetPosition") {
			if ((int)argv.size() < 3) { return; }
			component->SetPosition(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]));
			return;
		}
		if (propertyName == "SetOrientation") {
			if ((int)argv.size() < 4) { return; }
			component->SetOrientation(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]), StringUtilities::ConvertStringToFloat(argv[3]));
			return;
		}
		if (propertyName == "SetScale") {
			if ((int)argv.size() < 3) { return; }
			component->SetScale(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]));
			return;
		}
		if (propertyName == "Translate") {
			if ((int)argv.size() < 3) { return; }
			component->Translate(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]));
			return;
		}
		if (propertyName == "Rotate") {
			if ((int)argv.size() < 4) { return; }
			component->Rotate(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]), StringUtilities::ConvertStringToFloat(argv[3]));
			return;
		}
		if (propertyName == "Scale") {
			if ((int)argv.size() < 1) { return; }
			component->Scale(StringUtilities::ConvertStringToFloat(argv[0]));
			return;
		}
		if (propertyName == "LookAt") {
			if ((int)argv.size() < 3) { return; }
			component->LookAt(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]));
			return;
		}
		return;
	}
	
	if (componentName == "ParticleSystem") {
		ParticleSystem* component = gameObject->GetComponent<ParticleSystem>();
		if (component == nullptr) { return; }
		if (propertyName == "SetNumberOfParticles") {
			if ((int)argv.size() < 2) { return; }
			component->SetNumberOfParticles(StringUtilities::ConvertStringToInt(argv[0]), StringUtilities::ConvertStringToInt(argv[1]));
			return;
		}
		if (propertyName == "SetParticleSpeed") {
			if ((int)argv.size() < 2) { return; }
			component->SetParticleSpeed(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]));
			return;
		}
		if (propertyName == "SetParticleSize") {
			if ((int)argv.size() < 2) { return; }
			component->SetParticleSize(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]));
			return;
		}
		if (propertyName == "SetParticleLifespan") {
			if ((int)argv.size() < 1) { return; }
			component->SetParticleLifespan(StringUtilities::ConvertStringToFloat(argv[0]));
			return;
		}
		if (propertyName == "SetParticleTexture") {
			if ((int)argv.size() < 1) { return; }
			component->SetParticleTexture(ConvertStringToString(argv[0]));
			return;
		}
		if (propertyName == "SetParticleInitialColor") {
			if ((int)argv.size() < 4) { return; }
			component->SetParticleInitialColor(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]), StringUtilities::ConvertStringToFloat(argv[3]));
			return;
		}
		if (propertyName == "SetParticleFinalColor") {
			if ((int)argv.size() < 4) { return; }
			component->SetParticleFinalColor(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]), StringUtilities::ConvertStringToFloat(argv[3]));
			return;
		}
		if (propertyName == "SetParticleVelocityDirection") {
			if ((int)argv.size() < 3) { return; }
			component->SetParticleVelocityDirection(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]));
			return;
		}
		if (propertyName == "SetParticleVelocityDirectionRandomness") {
			if ((int)argv.size() < 1) { return; }
			component->SetParticleVelocityDirectionRandomness(StringUtilities::ConvertStringToFloat(argv[0]));
			return;
		}
		if (propertyName == "SetAccelerationAmount") {
			if ((int)argv.size() < 1) { return; }
			component->SetAccelerationAmount(StringUtilities::ConvertStringToFloat(argv[0]));
			return;
		}
		if (propertyName == "SetAccelerationDirection") {
			if ((int)argv.size() < 3) { return; }
			component->SetAccelerationDirection(StringUtilities::ConvertStringToFloat(argv[0]), StringUtilities::ConvertStringToFloat(argv[1]), StringUtilities::ConvertStringToFloat(argv[2]));
			return;
		}
		if (propertyName == "SetName") {
			if ((int)argv.size() < 1) { return; }
			component->SetName(ConvertStringToString(argv[0]));
			return;
		}
		if (propertyName == "InitParticleSystem") {
			if ((int)argv.size() < 0) { return; }
			component->InitParticleSystem();
			return;
		}
		if (propertyName == "Play") {
			if ((int)argv.size() < 0) { return; }
			component->Play();
			return;
		}
		if (propertyName == "Pause") {
			if ((int)argv.size() < 0) { return; }
			component->Pause();
			return;
		}
		if (propertyName == "SetLooping") {
			if ((int)argv.size() < 1) { return; }
			component->SetLooping(StringUtilities::ConvertStringToBool(argv[0]));
			return;
		}
		return;
	}
	
	if (componentName == "SampleGameScript") {
		SampleGameScript* component = gameObject->GetComponent<SampleGameScript>();
		if (component == nullptr) { return; }
		return;
	}
}