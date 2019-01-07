#pragma once
#include "EventGenerator.h"
#include "FSM_Class.h"

class EventHandler : public EventGenerator, public Fsm
{
public:
	EventHandler(Allegro * al, bool is_client);
	~EventHandler();

	void handle_event();

};

