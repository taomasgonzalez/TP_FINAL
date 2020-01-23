#pragma once
#include "Observer.h"
#include "Scene.h"
#include "CharacterActionsFSM.h"

class CharacterSceneObserver: public Observer
{
public:
	CharacterSceneObserver(Scene* scenario, Character* character);
	~CharacterSceneObserver();

	void update();
protected:
	Scene * scenario = NULL;
	virtual void perform_movement(Action_info action) = 0;
	CharacterActionsFSM* fsm = NULL;
	EventGenerator* ev_gen = NULL;
	void kill_character();
	Character* character = NULL;
private:
	void direction_to_deltas(Action_info* action);

};


