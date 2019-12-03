#include "ProyectilesActionsEventGenerator.h"



ProyectilesActionsEventGenerator::ProyectilesActionsEventGenerator(std::vector<ALLEGRO_TIMER*> timers) : MapThingEventGenerator(timers)
{

}


ProyectilesActionsEventGenerator::~ProyectilesActionsEventGenerator()
{
}


EventPackage * ProyectilesActionsEventGenerator::fetch_event() {
	update_allegro_timer_events();
	return EventGenerator::fetch_event();
}

void ProyectilesActionsEventGenerator::set_moving_timer(ALLEGRO_TIMER * moving_timer)
{
	this->moving_timer = moving_timer;
}
void ProyectilesActionsEventGenerator::set_falling_timer(ALLEGRO_TIMER * falling_timer)
{
	this->falling_timer = falling_timer;
}
void ProyectilesActionsEventGenerator::set_impacting_timer(ALLEGRO_TIMER* impacting_timer) {
	this->impacting_timer = impacting_timer;
}

void ProyectilesActionsEventGenerator::update_allegro_timer_events() {
	ALLEGRO_EVENT allegroEvent;
	EventPackage * ev_pack = NULL;

	if (al_get_next_event(timers_queue, &allegroEvent)) {
		if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
			//if (allegroEvent.timer.source == coordinate_scene_events_timer) {
				
			//}
		}
	}
}
