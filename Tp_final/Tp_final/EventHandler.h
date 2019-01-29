#pragma once
#include "EventGenerator.h"
#include "FSM_Class.h"

class EventHandler : public EventGenerator, public FSM
{
public:
	EventHandler(Allegro * al, Userdata * data);
	~EventHandler();

	void handle_event();

};

