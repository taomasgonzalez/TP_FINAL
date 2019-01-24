#pragma once
#include "Observer.h"
#include "FSM_Class.h"
#include "EventGenerator.h"
#include "EventHandler.h"
#include "Scene.h"
#include "EventPackage.h"
#include "Scene.h"



class FSMEventsObserver: public Observer
{
public:
	FSMEventsObserver(EventGenerator * event_gen, FSM * fsm, Allegro* allegro_container, Scene * scenario);
	~FSMEventsObserver();

	virtual void update();

private:
	EventGenerator * event_gen;
	FSM * fsm;
	Allegro * allegro_container;
	Scene * scenario;
};

