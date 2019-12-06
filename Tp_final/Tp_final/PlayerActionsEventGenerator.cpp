#include "PlayerActionsEventGenerator.h"



PlayerActionsEventGenerator::PlayerActionsEventGenerator(std::vector<ALLEGRO_TIMER*> timers, Player* player) : CharacterActionsEventGenerator(timers)
{
	this->player = player;
}


PlayerActionsEventGenerator::~PlayerActionsEventGenerator()
{
}
EventPackage* PlayerActionsEventGenerator::fetch_event() {
	update_allegro_timer_events();
	return EventGenerator::fetch_event();
}

void PlayerActionsEventGenerator::update_allegro_timer_events()
{
	ALLEGRO_EVENT allegroEvent;
	EventPackage * ev_pack = NULL;

	if (al_get_next_event(timers_queue, &allegroEvent)) {
		if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
			if (allegroEvent.timer.source == pushing_timer) {
				append_new_event(new PUSHED_EventPackage(Userdata::sense_2_direction(player->get_sense())), (int)MapThing_queues::Allegro);
			}
		}
	}
}


void PlayerActionsEventGenerator::set_pushing_timer(ALLEGRO_TIMER* pushing_timer) {
	this->pushing_timer = pushing_timer;
}