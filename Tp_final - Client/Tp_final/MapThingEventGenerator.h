#pragma once
#include "EventGenerator.h"

using namespace std;

class MapThingEventGenerator : public EventGenerator
{
public:
	enum class MapThing_queues { MapThingFSM, Allegro };

	MapThingEventGenerator(vector<ALLEGRO_TIMER*> timers);
	~MapThingEventGenerator();

protected:

	virtual void update_allegro_timer_events() = 0;
	
	ALLEGRO_EVENT_QUEUE* timers_queue = NULL;

};
