//
//  LevelManager.h
//  Created by Matt Kaufmann on 01/10/14.
//

#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

//#include "ExampleGame/Components/ShadyCamera/ShadyCamera.h"

#include "Vajra/Common/Components/Component.h"
//#include "Vajra/Engine/Ui/UiElement/UiElement.h"

#include <string>

//[[COMPONENT]]//
class LevelManager : public Component {
public:
	LevelManager();
	LevelManager(Object* object_);
	~LevelManager();

	void HandleMessage(MessageChunk messageChunk);

	inline std::string GetCurrentLevelName() { return this->currentLevelName; }

	//[[PROPERTY]]//
	void LoadLevelFromFile(std::string levelFilename);
	//void LoadLevelFromAsset(std::string assetName); // Once we've got the loading process worked out, switch to using an asset

private:
	void init();
	void destroy();
	void update();

	/*****************
	bool playerHasWonLevel();
	bool playerHasLostLevel();
	*****************/

	void endLevel(bool success);

	static ComponentIdType componentTypeId;

	//ShadyCamera* shadyCam;
	bool isPaused;
	std::string currentLevelName;

	//UiElement* levelTutorial;

	/*****************
	These are all from the Unity prototype but will probably be deprecated
	******************
	std::vector<EndCondition*> winCons; // Probably deprecate this
	std::vector<EndCondition*> loseCons; // This too
	int PLAYER_THREATS;
	*****************/
};

#endif // LEVELMANAGER_H
