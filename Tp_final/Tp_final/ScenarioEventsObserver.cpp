#include "ScenarioEventsObserver.h"

ScenarioEventsObserver::ScenarioEventsObserver(EventGenerator * event_gen, Scene * scenario)
{
	this->event_gen = event_gen;
	this->scenario = scenario;
}


ScenarioEventsObserver::~ScenarioEventsObserver()
{
}

void ScenarioEventsObserver::update() {
	if (this->scenario->should_init) {
		EventPackage * evento_de_inicializion = new EventPackage();
		evento_de_inicializion->ev = Event::START_COMMUNICATION;
		this->event_gen->soft_queue->push(evento_de_inicializion);
		this->scenario->should_init = false;
	}
	//if(gam)

	//EventPackage * new_ev_pack = new EventPackage();

	//filtrado de informacion!!

	//event_gen->soft_queue->push(new_ev_pack);
}
