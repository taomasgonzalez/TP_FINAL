#pragma once
#include "EventGenerator.h"
#include "FSM_Class.h"

class EventHandler
{
public:
	EventHandler(FSM * fsm, EventGenerator* ev_gen);
	~EventHandler();

	void handle_event();

	FSM * get_fsm();
	EventGenerator* get_ev_gen();

private:
	FSM * fsm;
	EventGenerator* ev_gen;
};

