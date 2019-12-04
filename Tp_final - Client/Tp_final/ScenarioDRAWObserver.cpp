#include "ScenarioDRAWObserver.h"


ScenarioDRAWObserver::ScenarioDRAWObserver(Scene* scenario, DRAW* drawer)
{
	this->scenario = scenario;
	this->drawer = drawer;
}


ScenarioDRAWObserver::~ScenarioDRAWObserver()
{
}

void ScenarioDRAWObserver::update() {
	if (scenario->load_graphic_level) {
		drawer->add_level(scenario->give_me_the_map_info());
	}
}
