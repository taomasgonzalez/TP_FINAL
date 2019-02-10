#pragma once
#include "EventGenerator.h"
#include "FSM_Class.h"

class EventHandler
{
public:
	EventHandler(FSM * fsm, EventGenerator* ev_gen);
	~EventHandler();

	void handle_event();

private:
	FSM * fsm;
	EventGenerator* ev_gen;
};

