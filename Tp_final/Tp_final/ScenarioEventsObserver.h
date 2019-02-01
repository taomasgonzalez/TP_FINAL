#pragma once
#include "Observer.h"
#include "EventHandler.h"
#include "Scene.h"
#include "EventPackage.h"

class ScenarioEventsObserver: public Observer
{
public:
	ScenarioEventsObserver(EventHandler * event_gen, Scene * scenario, FSM * fsm, Userdata * data);
	~ScenarioEventsObserver();

	void update();

private:
	EventHandler * my_event_handler;
	Scene * scenario;
	FSM * my_fsm;
	Userdata * my_user_data;
};

