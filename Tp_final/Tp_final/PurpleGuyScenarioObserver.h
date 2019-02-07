#pragma once
#include "EnemyScenarioObserver.h"
#include "PurpleGuy.h"

class PurpleGuyScenarioObserver:public EnemyScenarioObserver
{
public:
	PurpleGuyScenarioObserver(PurpleGuy* purple_guy, Scene* scene);
	~PurpleGuyScenarioObserver();

	void update();
protected:
	PurpleGuy * purple_guy;
};

