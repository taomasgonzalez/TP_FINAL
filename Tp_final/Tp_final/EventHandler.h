#pragma once
#include "EventGenerator.h"
#include "FSM_Class.h"

class EventHandler : public EventGenerator
{
public:
	EventHandler(Allegro * al, FSM* fsm, Userdata * data);
	~EventHandler();

	void handle_event();

};

