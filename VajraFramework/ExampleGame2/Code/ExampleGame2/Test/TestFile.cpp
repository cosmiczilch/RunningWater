#include "ExampleGame2/Components/GameScripts/SampleGameScript.h"
#include "ExampleGame2/Components/GameScripts/Units/BaseUnit.h"
#include "ExampleGame2/Components/GameScripts/Units/PlayerUnit.h"
#include "ExampleGame2/Components/Grid/GridManager.h"
#include "ExampleGame2/Components/Grid/GridNavigator.h"
#include "ExampleGame2/Components/Grid/GridZone.h"
#include "ExampleGame2/Components/ShadyCamera/ShadyCamera.h"
#include "ExampleGame2/GameSingletons/GameSingletons.h"
#include "ExampleGame2/Test/TestFile.h"
#include "ExampleGame2/Ui/TouchHandlers/TestUiSceneTouchHandlers.h"
#include "Vajra/Common/Objects/Object.h"
#include "Vajra/Engine/Components/DerivedComponents/Renderer/MeshRenderer.h"
#include "Vajra/Engine/Components/DerivedComponents/Transform/Transform.h"
#include "Vajra/Engine/Core/Engine.h"
#include "Vajra/Engine/GameObject/GameObject.h"
#include "Vajra/Engine/Prefabs/PrefabLoader.h"
#include "ExampleGame2/ComponentMapper/ComponentMapper.h"
#include "Vajra/Engine/SceneGraph/SceneGraph3D.h"
#include "Vajra/Engine/SceneGraph/SceneGraphUi.h"
#include "Vajra/Engine/SceneLoaders/UiSceneLoader/UiSceneLoader.h"
#include "Vajra/Engine/TagManager/TagManager.h"
#include "Vajra/Framework/Core/Framework.h"
#include "Vajra/Framework/DeviceUtils/FileSystemUtils/FileSystemUtils.h"
#include "Vajra/Framework/Logging/Logger.h"

// Forward Declarations:
void initUiGameObjects();

int TestFuntion() {
	// Instantiate a ComponentMapper so that its singleton gets stored:
	/* ComponentMapper* componentMapper = */ new ComponentMapper();

	{
#if 1
		/*GameObject* gameObject = */PrefabLoader::InstantiateGameObjectFromPrefab(
							    	 FRAMEWORK->GetFileSystemUtils()->GetDevicePrefabsResourcesPath() + "test.prefab",
						   	     	 ENGINE->GetSceneGraph3D());
#endif
	}
	{
#if 1
		/*GameObject* gameObject = */PrefabLoader::InstantiateGameObjectFromPrefab(
							    	 FRAMEWORK->GetFileSystemUtils()->GetDevicePrefabsResourcesPath() + "fire_0.prefab",
						   	     	 ENGINE->GetSceneGraph3D());
#endif
	}
	{
#if 1
		/*GameObject* gameObject = */PrefabLoader::InstantiateGameObjectFromPrefab(
							    	 FRAMEWORK->GetFileSystemUtils()->GetDevicePrefabsResourcesPath() + "fire_1.prefab",
						   	     	 ENGINE->GetSceneGraph3D());
#endif
	}
	{
#if 1
		/*GameObject* gameObject = */PrefabLoader::InstantiateGameObjectFromPrefab(
							    	 FRAMEWORK->GetFileSystemUtils()->GetDevicePrefabsResourcesPath() + "fire_2.prefab",
						   	     	 ENGINE->GetSceneGraph3D());
#endif
	}
	{
#if 1
		/*GameObject* gameObject = */PrefabLoader::InstantiateGameObjectFromPrefab(
							    	 FRAMEWORK->GetFileSystemUtils()->GetDevicePrefabsResourcesPath() + "fire_3.prefab",
						   	     	 ENGINE->GetSceneGraph3D());
#endif
	}


	initUiGameObjects();

	return 4;
}

void initUiGameObjects() {
	{
		GameObject* camera = new GameObject(ENGINE->GetSceneGraphUi());
		ENGINE->GetSceneGraphUi()->GetRootGameObject()->AddChild(camera->GetId());
		Camera* cameraComponent = camera->AddComponent<Camera>();
		cameraComponent->SetCameraType(CAMERA_TYPE_ORTHO);
		camera->GetTransform()->SetPosition(0.0f, 0.0f, 400.0f);
		camera->GetTransform()->Rotate(10.0f inRadians, YAXIS);
		// camera->GetTransform()->SetOrientation(-45.0f inRadians, camera->GetTransform()->GetUp());
		// camera->GetTransform()->Rotate(45.0f inRadians, camera->GetTransform()->GetLeft());
		camera->GetTransform()->LookAt(0.0f, 0.0f, 0.0f);
		ENGINE->GetSceneGraphUi()->SetMainCameraId(camera->GetId());
	}

	{
		std::string pathToTestUiScene = FRAMEWORK->GetFileSystemUtils()->GetDeviceUiScenesResourcesPath() + "testUiScene.uiscene";
		UiSceneLoader::LoadUiSceneFromUiSceneFile(pathToTestUiScene.c_str(), new TestUiSceneTouchHandlers());
	}
}
