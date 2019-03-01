#pragma once
#include "EventGenerator.h"
#include "AllegroClass.h"
class CharacterActionsEventGenerator: public EventGenerator
{
public:
	CharacterActionsEventGenerator(std::vector<ALLEGRO_TIMER*> timers);
	~CharacterActionsEventGenerator();

	EventPackage * fetch_event();
protected:

	ALLEGRO_EVENT_QUEUE * character_timers_queue = NULL;
};

