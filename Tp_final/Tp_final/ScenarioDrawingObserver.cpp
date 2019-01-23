#include "ScenarioDrawingObserver.h"



ScenarioDrawingObserver::ScenarioDrawingObserver( Scene* scenario, Drawer* my_drawer)
{
	this->drawer = my_drawer;
	this->scenario = scenario;
}


ScenarioDrawingObserver::~ScenarioDrawingObserver()
{
}

void ScenarioDrawingObserver::update() {

	if(scenario->has_to_draw)
		this->drawer->draw(scenario);
}

