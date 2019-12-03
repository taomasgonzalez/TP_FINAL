#pragma once
#include "Observer.h"
#include "Scene.h"
#include "DRAW.h"

class ScenarioDRAWObserver : public Observer
{
public:
	ScenarioDRAWObserver(Scene* scenario, DRAW* drawer);
	~ScenarioDRAWObserver();

	void update();
	
private: 
	Scene * scenario = NULL;
	DRAW* drawer = NULL;

};

