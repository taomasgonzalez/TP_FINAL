#pragma once
#include "EventGenerator.h"
#include "FSM_Class.h"

class EventHandler
{
public:
	EventHandler(FSM * fsm, EventGenerator* ev_gen, Allegro* al, Userdata * data);
	~EventHandler();

	void handle_event();

private:
	FSM * fsm;
	EventGenerator* ev_gen;
	Userdata * my_user_data;
	Allegro * al;
};

