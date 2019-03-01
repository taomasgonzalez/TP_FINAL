#include "CharacterActionsEventGenerator.h"



CharacterActionsEventGenerator::CharacterActionsEventGenerator(std::vector<ALLEGRO_TIMER*> timers)
{
	append_all_queues(2);

	character_timers_queue = al_create_event_queue();

	for (std::vector<ALLEGRO_TIMER*>::iterator it = timers.begin(); it != timers.end(); ++it) 
		al_register_event_source(character_timers_queue, al_get_timer_event_source(*it));
}


CharacterActionsEventGenerator::~CharacterActionsEventGenerator()
{
}


EventPackage * CharacterActionsEventGenerator::fetch_event() {
	return new EventPackage(Event_type::NO_EVENT, true);
}
