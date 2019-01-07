#pragma once
#include "Observer.h"
#include "FSM_Class.h"
#include "EventGenerator.h"
//#include "Allegroclass.h"

class FSMEventsObserver: public Observer
{
public:
	FSMEventsObserver(EventGenerator * event_gen, Fsm * fsm);
	~FSMEventsObserver();

	virtual void update();

	EventGenerator * event_gen;
	Fsm * fsm;
	Allegro * allegro_container;
};

