#include "MapThingEventGenerator.h"



MapThingEventGenerator::MapThingEventGenerator(std::vector<ALLEGRO_TIMER*> timers)
{
	append_all_queues(2);

	timers_queue = al_create_event_queue();

	for (std::vector<ALLEGRO_TIMER*>::iterator it = timers.begin(); it != timers.end(); ++it)
		al_register_event_source(timers_queue, al_get_timer_event_source(*it));
}


MapThingEventGenerator::~MapThingEventGenerator()
{
}

