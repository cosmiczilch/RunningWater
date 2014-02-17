#include "Vajra/Common/Messages/CustomMessageDatas/MessageData1S1I1F.h"
#include "Vajra/Engine/Components/DerivedComponents/Armature/Armature.h"
#include "Vajra/Engine/Components/DerivedComponents/Audio/AudioSource.h"
#include "Vajra/Engine/Components/DerivedComponents/Camera/Camera.h"
#include "Vajra/Engine/Components/DerivedComponents/Lights/DirectionalLight/DirectionalLight.h"
#include "Vajra/Engine/Components/DerivedComponents/Animation/AnimationClip/AnimationClip.h"
#include "Vajra/Engine/Components/DerivedComponents/Animation/BakedSkeletalAnimation/BakedSkeletalAnimation.h"
#include "Vajra/Engine/Components/DerivedComponents/Animation/RigidAnimation/RigidAnimation.h"
#include "Vajra/Engine/Components/DerivedComponents/Renderer/MeshRenderer.h"
#include "Vajra/Engine/Components/DerivedComponents/Renderer/UiFontRenderer.h"
#include "Vajra/Engine/Components/DerivedComponents/Transform/Transform.h"
#include "Vajra/Engine/Core/Engine.h"
#include "Vajra/Engine/DebugDrawer/DebugDrawer.h"
#include "Vajra/Engine/GameObject/GameObject.h"
#include "Vajra/Engine/MessageHub/MessageHub.h"
#include "Vajra/Engine/Prefabs/PrefabLoader.h"
#include "Vajra/Engine/Tween/Tween.h"
#include "Vajra/Engine/SceneGraph/SceneGraph3D.h"
#include "Vajra/Engine/SceneGraph/SceneGraphUi.h"
#include "Vajra/Engine/SceneLoaders/UiSceneLoader/UiSceneLoader.h"
#include "Vajra/Engine/Ui/UiElement/UiElement.h"
#include "Vajra/Framework/DeviceUtils/FileSystemUtils/FileSystemUtils.h"
#include "Vajra/Framework/Logging/Logger.h"
#include "Vajra/Framework/OpenGL/OpenGLWrapper/OpenGLWrapper.h"
#include "Vajra/Framework/OpenGL/ShaderSet/ShaderSet.h"
#include "Vajra/Placeholder/Tesserakonteres.h"
#include "Vajra/Utilities/XmlParser/XmlParser.h"

#include "Libraries/glm/glm.hpp"
#include "Libraries/glm/gtx/transform.hpp"
#include "Libraries/glm/gtc/type_ptr.hpp"

#include <vector>


namespace Tesserakonteres {

	void tweenCallback(ObjectIdType gameObjectId, std::string tweenClipName) {
		FRAMEWORK->GetLogger()->dbglog("\nIn tweenCallback() with %d, %s\n", gameObjectId, tweenClipName.c_str());
	}

	void tweenNumberCallback(float /* fromNumber */, float /* toNumber */, float /* currentNumber */, std::string /* tweenName */, MessageData1S1I1F* /* userParams */) {
#if 0
		if (userParams != nullptr) {
			FRAMEWORK->GetLogger()->dbglog("\nIn tweenNumberCallback() (%s) with current number %f, and userParam.number %d", tweenName.c_str(), currentNumber, userParams->i);
		}
#endif
		// if (currentNumber > 5.0f) {
			// ENGINE->GetTween()->CancelNumberTween("numbertween");
			// ENGINE->GetTween()->CancelPostitionTween(118);
		// }
#if 0
		if (tweenName == "tween_stubby_arrows") {
			GameObject* gameObject = ENGINE->GetSceneGraph3D()->GetGameObjectById(115);
			if (gameObject != nullptr) {
				gameObject->GetTransform()->SetPosition(0.0f, 0.0f, normalizedProgress);
			}
		}
#endif
	}

	void initGameObjectsForScene() {

		{
			GameObject* camera = new GameObject(ENGINE->GetSceneGraph3D());
			ENGINE->GetSceneGraph3D()->GetRootGameObject()->AddChild(camera->GetId());
			Camera* cameraComponent = camera->AddComponent<Camera>();
			cameraComponent->SetCameraType(CAMERA_TYPE_PERSPECTIVE);
			camera->GetTransform()->SetPosition(20.0f, 20.0f, 20.0f);
			// camera->GetTransform()->SetOrientation(-45.0f, camera->GetTransform()->GetUp());
			// camera->GetTransform()->Rotate(45.0f inRadians, camera->GetTransform()->GetLeft());
			camera->GetTransform()->LookAt(0.0f, 0.0f, 0.0f);
			ENGINE->GetSceneGraph3D()->SetMainCameraId(camera->GetId());
		}
		{
			GameObject* dlight = new GameObject(ENGINE->GetSceneGraph3D());
			ENGINE->GetSceneGraph3D()->GetRootGameObject()->AddChild(dlight->GetId());
			DirectionalLight* dlightComponent = dlight->AddComponent<DirectionalLight>();
			dlight->GetTransform()->SetPosition(0.0f, 0.0f, 0.0f);
			dlight->GetTransform()->LookAt(0.5f, 10.0f, 0.5f);
			ENGINE->GetSceneGraph3D()->SetMainDirectionalLightId(dlight->GetId());
			//
			dlightComponent->SetAmbientColor(0.15f, 0.15f, 0.3f, 1.0f);
			dlightComponent->SetDiffuseColor(0.5f, 0.5f, 0.55f, 1.0f);
		}


		MessageData1S1I1F* userParams = new MessageData1S1I1F();
		userParams->i = 9001;
		ENGINE->GetTween()->TweenToNumber(-20.0f, 20.0f, 20.0f, true, true, true, "numbertween", userParams, tweenNumberCallback);

		FRAMEWORK->GetLogger()->dbglog("\nDone loading game objects for the scene");
	}

}
