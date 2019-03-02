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
protected:
	virtual void perform_movement(Action_info action) = 0;
	Scene * scenario = NULL;
	CharacterActionsFSM* fsm = NULL;
	CharacterActionsEventGenerator* ev_gen = NULL;
private:
	Character* character = NULL;
	void kill_character();
	void append_action_to_character(Action_info action);
};


