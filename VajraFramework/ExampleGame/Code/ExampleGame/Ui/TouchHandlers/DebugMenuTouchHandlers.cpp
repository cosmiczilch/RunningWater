#ifdef DEBUG
#include "ExampleGame/Ui/TouchHandlers/DebugMenuTouchHandlers.h"
#include "ExampleGame/Ui/TouchHandlers/GameUiTouchHandlers.h"
#include "Vajra/Engine/Components/DerivedComponents/Camera/Camera.h"
#include "Vajra/Engine/Components/DerivedComponents/Transform/Transform.h"
#include "Vajra/Engine/SceneGraph/SceneGraphUi.h"
#include "Vajra/Engine/SceneLoaders/UiSceneLoader/UiSceneLoader.h"
#include "Vajra/Engine/Ui/UiElement/UiElement.h"
#include "Vajra/Engine/Ui/UiObject/UiObject.h"
#include "Vajra/Framework/Core/Framework.h"
#include "Vajra/Framework/Logging/Logger.h"

// Todo [HACK] when level loading is better we probably won't need all these
#include "Vajra/Framework/DeviceUtils/FileSystemUtils/FileSystemUtils.h"
#include "Vajra/Engine/Core/Engine.h"
#include "Vajra/Engine/GameObject/GameObject.h"
#include "ExampleGame/GameSingletons/GameSingletons.h"
#include "Vajra/Engine/SceneGraph/SceneGraph3D.h"

#define TEXTURE_INDEX_BUTTON_UP 0
#define TEXTURE_INDEX_BUTTON_DOWN 1

DebugMenuTouchHandlers::DebugMenuTouchHandlers() : UiTouchHandlers() {
	this->cameraSpeed = 2.0f;

	GameObject* debugCam = new GameObject(ENGINE->GetSceneGraph3D());
	ENGINE->GetSceneGraph3D()->GetRootGameObject()->AddChild(debugCam->GetId());
	Camera* camComponent = debugCam->AddComponent<Camera>();
	camComponent->SetFOV(30.0f inRadians);
	
	GameObject* shadyCam = (GameObject*)ENGINE->GetSceneGraph3D()->GetMainCamera()->GetObject();
	debugCam->GetTransform()->SetPosition(shadyCam->GetTransform()->GetPosition());
	debugCam->GetTransform()->SetOrientation(shadyCam->GetTransform()->GetOrientation());
	
	this->shadyCamId = shadyCam->GetId();
	ENGINE->GetSceneGraph3D()->SetMainCameraId(debugCam->GetId());
}

void DebugMenuTouchHandlers::OnTouchDownHandlers(UiObject* uiObject, Touch /*touch*/ ) {
	if (uiObject->GetUiObjectName() == "touchPad") {
		// Do something

	} else if (uiObject->GetUiObjectName() == "up") {
		// TODO [Implement] Ensure type safety here
		((UiElement*)uiObject)->SetSpriteTextureIndex(TEXTURE_INDEX_BUTTON_DOWN);
	} else if (uiObject->GetUiObjectName() == "down") {
		// TODO [Implement] Ensure type safety here
		((UiElement*)uiObject)->SetSpriteTextureIndex(TEXTURE_INDEX_BUTTON_DOWN);
	} else if (uiObject->GetUiObjectName() == "left") {
		// TODO [Implement] Ensure type safety here
		((UiElement*)uiObject)->SetSpriteTextureIndex(TEXTURE_INDEX_BUTTON_DOWN);
	} else if (uiObject->GetUiObjectName() == "right") {
		// TODO [Implement] Ensure type safety here
		((UiElement*)uiObject)->SetSpriteTextureIndex(TEXTURE_INDEX_BUTTON_DOWN);
	} else {
		// Do something

	}
}

void DebugMenuTouchHandlers::OnTouchMoveHandlers(UiObject* uiObject, Touch touch ) {
	if (uiObject->GetUiObjectName() == "touchPad") {
		// Do something
		glm::vec2 moveDir = touch.pos - touch.prevPos;
		GameObject* debugCam = (GameObject*)ENGINE->GetSceneGraph3D()->GetMainCamera()->GetObject();
		Transform* trans = debugCam->GetTransform();

		trans->Rotate(-moveDir.x inRadians, YAXIS);
		trans->Rotate(moveDir.y inRadians, trans->GetLeft());

	} else {
		// Do something

	}
}


void DebugMenuTouchHandlers::OnTouchUpHandlers(UiObject* uiObject, Touch /* touch */) {
	GameObject* debugCam = (GameObject*)ENGINE->GetSceneGraph3D()->GetMainCamera()->GetObject();
	Transform* trans = debugCam->GetTransform();
	if (uiObject->GetUiObjectName() == "up") {
		trans->Translate(this->cameraSpeed, trans->GetForward());
		// TODO [Implement] Ensure type safety here
		((UiElement*)uiObject)->SetSpriteTextureIndex(TEXTURE_INDEX_BUTTON_UP);
	} else if (uiObject->GetUiObjectName() == "down") {
		trans->Translate(-this->cameraSpeed, trans->GetForward());
		// TODO [Implement] Ensure type safety here
		((UiElement*)uiObject)->SetSpriteTextureIndex(TEXTURE_INDEX_BUTTON_UP);
	} else if (uiObject->GetUiObjectName() == "left") {
		trans->Translate(this->cameraSpeed, trans->GetLeft());
		// TODO [Implement] Ensure type safety here
		((UiElement*)uiObject)->SetSpriteTextureIndex(TEXTURE_INDEX_BUTTON_UP);
	} else if (uiObject->GetUiObjectName() == "right") {
		trans->Translate(-this->cameraSpeed, trans->GetLeft());
		// TODO [Implement] Ensure type safety here
		((UiElement*)uiObject)->SetSpriteTextureIndex(TEXTURE_INDEX_BUTTON_UP);
	} else if (uiObject->GetUiObjectName() == "back") {
		std::string pathToTestUiScene = FRAMEWORK->GetFileSystemUtils()->GetDeviceUiScenesResourcesPath() + "gameUi.uiscene";
		UiSceneLoader::LoadUiSceneFromUiSceneFile(pathToTestUiScene.c_str(), new GameUiTouchHandlers());


		GameObject* debugCam = (GameObject*)ENGINE->GetSceneGraph3D()->GetMainCamera()->GetObject();
		ENGINE->GetSceneGraph3D()->SetMainCameraId(this->shadyCamId);
		delete debugCam;
	}
}
#endif
