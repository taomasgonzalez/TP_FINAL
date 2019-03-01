#pragma once
#include "Observer.h"
#include "Scene.h"
#include "CharacterActionsFSM.h"
#include "CharacterActionsEventGenerator.h"

class CharacterSceneObserver: public Observer
{
public:
	CharacterSceneObserver(Scene* scenario, Character* character);
	~CharacterSceneObserver();

	void update();
private:
	Scene * scenario = NULL;
	Character* character = NULL;
	CharacterActionsFSM* fsm = NULL;
	CharacterActionsEventGenerator* ev_gen = NULL;

	void kill_character();
};


