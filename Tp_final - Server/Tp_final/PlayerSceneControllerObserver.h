#pragma once
#include "Observer.h"
#include "Scene.h"
#include "CharacterActionsFSM.h"


class PlayerSceneControllerObserver :public Observer
{
public:
	PlayerSceneControllerObserver(Scene *my_scenario, Character* character);
	~PlayerSceneControllerObserver();

	void update();

private:
	Scene * scenario;
	CharacterActionsFSM * fsm;
	Character* character = NULL;

};

