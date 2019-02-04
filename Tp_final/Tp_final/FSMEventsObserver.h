#pragma once
#include "Observer.h"
#include "FSM_Class.h"
#include "LogicEventGenerator.h"
#include "Scene.h"
#include "EventPackage.h"
#include "Scene.h"



class FSMEventsObserver: public Observer
{
public:
	FSMEventsObserver(LogicEventGenerator * event_gen, FSM * fsm, Allegro* allegro_container, Scene * scenario);
	~FSMEventsObserver();

	virtual void update();

private:
	LogicEventGenerator * event_gen;
	FSM * fsm;
	Allegro * allegro_container;
	Scene * scenario;
};

