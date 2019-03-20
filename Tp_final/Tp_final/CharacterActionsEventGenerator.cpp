#include "CharacterActionsEventGenerator.h"



CharacterActionsEventGenerator::CharacterActionsEventGenerator(std::vector<ALLEGRO_TIMER*> timers) :MapThingEventGenerator(timers)
{

}


CharacterActionsEventGenerator::~CharacterActionsEventGenerator()
{
}

EventPackage* CharacterActionsEventGenerator::fetch_event() {
	update_allegro_timer_events();
	return EventGenerator::fetch_event();
}
void CharacterActionsEventGenerator::set_walking_timer(ALLEGRO_TIMER * walking_timer)
{
	this->walking_timer = walking_timer;
}
void CharacterActionsEventGenerator::set_jumping_timer(ALLEGRO_TIMER * jumping_timer)
{
	this->jumping_timer = jumping_timer;
}
void CharacterActionsEventGenerator::set_jumping_forward_timer(ALLEGRO_TIMER * jumping_forward_timer)
{
	this->jumping_forward_timer = jumping_forward_timer;
}
void CharacterActionsEventGenerator::set_falling_timer(ALLEGRO_TIMER * falling_timer)
{
	this->falling_timer = falling_timer;
}
void CharacterActionsEventGenerator::set_attacking_timer(ALLEGRO_TIMER * attacking_timer)
{
	this->attacking_timer = attacking_timer;
}

void CharacterActionsEventGenerator::update_allegro_timer_events() {
	ALLEGRO_EVENT allegroEvent;
	EventPackage * ev_pack = NULL;

	if (al_get_next_event(timers_queue, &allegroEvent)) {
		if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
			if (allegroEvent.timer.source == walking_timer) {
				append_new_event(new MOVE_EventPackage(),(int) MapThing_queues::Allegro);
			}
			else if (allegroEvent.timer.source == jumping_timer) {
				append_new_event(new MOVE_EventPackage(), (int)MapThing_queues::Allegro);
			}
			else if (allegroEvent.timer.source == jumping_forward_timer) {
				append_new_event(new MOVE_EventPackage(), (int)MapThing_queues::Allegro);
			}
			else if (allegroEvent.timer.source == falling_timer) {
				append_new_event(new MOVE_EventPackage(), (int)MapThing_queues::Allegro);
			}
			else if (allegroEvent.timer.source == attacking_timer) {
				append_new_event(new ATTACK_EventPackage(), (int)MapThing_queues::Allegro);
			}
		}
	}
}


