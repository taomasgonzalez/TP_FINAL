#include "EnemyActionsEventGenerator.h"



EnemyActionsEventGenerator::EnemyActionsEventGenerator(std::vector<ALLEGRO_TIMER*> timers) : CharacterActionsEventGenerator(timers)
{
}


EnemyActionsEventGenerator::~EnemyActionsEventGenerator()
{
}
EventPackage* EnemyActionsEventGenerator::fetch_event() {
	update_allegro_timer_events();
	return EventGenerator::fetch_event();
}

void EnemyActionsEventGenerator::update_allegro_timer_events()
{
	ALLEGRO_EVENT allegroEvent;
	EventPackage * ev_pack = NULL;

	if (al_get_next_event(timers_queue, &allegroEvent)) {
		if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
			if (allegroEvent.timer.source == frozen_timer) {

			}
			else if (allegroEvent.timer.source == freezing_timer) {

			}
		}
	}
}


void EnemyActionsEventGenerator::set_frozen_timer(ALLEGRO_TIMER* frozen_timer) {
	this->frozen_timer = frozen_timer;
}
void EnemyActionsEventGenerator::set_freezing_timer(ALLEGRO_TIMER* freezing_timer) {
	this->freezing_timer = freezing_timer;
}