#ifndef UNIT_DECLARATIONS_H
#define UNIT_DECLARATIONS_H

#include "Libraries/glm/glm.hpp"

enum UnitState {
	UNIT_STATE_ALIVE,
	UNIT_STATE_DEAD
};

enum UnitType {
	UNIT_TYPE_ASSASSIN,
	UNIT_TYPE_THIEF,
	UNIT_TYPE_IMPOSTOR,
	UNIT_TYPE_PLAYER_UNITS_COUNT,
	UNIT_TYPE_GUARD,
	UNIT_TYPE_TARGET,
	UNIT_TYPE_CAPTAIN,
	UNIT_TYPE_UNKNOWN,
};
const UnitType FIRST_PLAYER_UNIT_TYPE = UNIT_TYPE_ASSASSIN;

enum InputState {
	INPUT_STATE_WAIT,
	INPUT_STATE_NAV,
	INPUT_STATE_SPECIAL
};

enum UnitActionState {
	UNIT_ACTION_STATE_IDLE,
	UNIT_ACTION_STATE_WALKING,
	UNIT_ACTION_STATE_DOING_SPECIAL,
};

struct UnitColorScheme {
	glm::vec4 baseColor;
	glm::vec4 uiColor;
	glm::vec4 effectColor;
};
#endif // UNIT_DECLARATIONS_H