#pragma once
#include "EnemySceneObserver.h"
#include "PurpleGuy.h"

class PurpleGuyScenarioObserver:public EnemySceneObserver
{
public:
	PurpleGuyScenarioObserver(PurpleGuy* purple_guy, Scene* scene);
	~PurpleGuyScenarioObserver();

	void update();
protected:
	PurpleGuy * purple_guy;
};

