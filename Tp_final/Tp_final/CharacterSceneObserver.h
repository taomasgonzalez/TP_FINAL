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
	virtual void perform_character_movement(EventPackage* action, bool& should_die, bool& should_hit);
private:
	Scene * scenario = NULL;
	Character* character = NULL;
	CharacterActionsFSM* fsm = NULL;
	CharacterActionsEventGenerator* ev_gen = NULL;

	void kill_character();
	void append_action_to_character(Action_info action);
};


