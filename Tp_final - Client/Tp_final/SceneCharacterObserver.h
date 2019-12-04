#pragma once
#include "Observer.h"
#include "Scene.h"
#include "CharacterActionsFSM.h"
#include "CharacterActionsEventGenerator.h"

class SceneCharacterObserver
{
public:
	SceneCharacterObserver(Scene* scenario, Character* character);
	~SceneCharacterObserver();

	void update();

private:
	Scene * scenario = NULL;
	Character* character = NULL;
	CharacterActionsFSM* fsm = NULL;
	CharacterActionsEventGenerator* ev_gen = NULL;

	void append_action_to_character(Action_info action);

};

