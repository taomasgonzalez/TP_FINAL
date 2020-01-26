#pragma once
#include "Observer.h"
#include "LogicEventGenerator.h"
#include "Scene.h"
#include "EventPackage.h"
#include "LogicFSM.h"


class ScenarioEventsObserver: public Observer
{
public:
	ScenarioEventsObserver(LogicEventGenerator * event_gen, Scene * scenario, LogicFSM * fsm, Userdata * data);
	~ScenarioEventsObserver();

	void update();

private:
	LogicEventGenerator * ev_gen;
	Scene * scenario;
	LogicFSM * my_fsm;
	Userdata * my_user_data;
};

