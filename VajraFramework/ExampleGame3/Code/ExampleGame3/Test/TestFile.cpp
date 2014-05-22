#include "Vajra/Engine/Components/DerivedComponents/Camera/Camera.h"
#include "ExampleGame3/Components/GameScripts/SampleGameScript.h"
#include "ExampleGame3/Simulation/Simulation.h"
#include "ExampleGame3/Test/TestFile.h"
#include "ExampleGame3/Ui/TouchHandlers/TestUiSceneTouchHandlers.h"
#include "Vajra/Common/Objects/Object.h"
#include "Vajra/Engine/Components/DerivedComponents/Renderer/MeshRenderer.h"
#include "Vajra/Engine/Components/DerivedComponents/Transform/Transform.h"
#include "Vajra/Engine/Core/Engine.h"
#include "Vajra/Engine/GameObject/GameObject.h"
#include "Vajra/Engine/Prefabs/PrefabLoader.h"
#include "ExampleGame3/ComponentMapper/ComponentMapper.h"
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



	initUiGameObjects();

	SIMULATION->BeginSimulation();

	return 4;
}

void initUiGameObjects() {
	{
		std::string pathToTestUiScene = FRAMEWORK->GetFileSystemUtils()->GetDeviceUiScenesResourcesPath() + "testUiScene.uiscene";
		UiSceneLoader::LoadUiSceneFromUiSceneFile(pathToTestUiScene.c_str(), new TestUiSceneTouchHandlers());
	}
}
