#pragma once
#include "Observer.h"
#include "LogicFSM.h"
#include "LogicEventGenerator.h"
#include "Scene.h"
#include "EventPackage.h"


class LogicFSMEventsObserver : public Observer
{
public:
	LogicFSMEventsObserver(LogicEventGenerator * event_gen, LogicFSM * fsm, Allegro* allegro_container, Userdata* data, Scene* scene);
	~LogicFSMEventsObserver();

	virtual void update();

private:
	LogicEventGenerator * event_gen;
	LogicFSM * fsm;
	Allegro * allegro_container;
	Scene* scenario;
	Userdata* my_user_data;
};

