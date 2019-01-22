#pragma once
#include "Observer.h"
#include "EventHandler.h"
#include "Scene.h"

class ScenarioEventsObserver: public Observer
{
public:
	ScenarioEventsObserver(EventHandler * event_gen, Scene * scenario);
	~ScenarioEventsObserver();

	virtual void update();

	EventHandler * my_event_handler;
	Scene * scenario;
};

