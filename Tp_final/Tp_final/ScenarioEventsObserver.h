#pragma once
#include "Observer.h"
#include "EventGenerator.h"
#include "Scene.h"

class ScenarioEventsObserver: public Observer
{
public:
	ScenarioEventsObserver(EventGenerator * event_gen, Scene * scenario);
	~ScenarioEventsObserver();

	virtual void update();

	EventGenerator * event_gen;
	Scene * scenario;
};

