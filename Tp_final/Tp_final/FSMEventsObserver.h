#pragma once
#include "Observer.h"
#include "LogicFSM.h"
#include "LogicEventGenerator.h"
#include "Scene.h"
#include "EventPackage.h"
#include "Scene.h"



class FSMEventsObserver: public Observer
{
public:
	FSMEventsObserver(LogicEventGenerator * event_gen, LogicFSM * fsm, Allegro* allegro_container, Scene * scenario);
	~FSMEventsObserver();

	virtual void update();

private:
	LogicEventGenerator * event_gen;
	LogicFSM * fsm;
	Allegro * allegro_container;
	Scene * scenario;
};

