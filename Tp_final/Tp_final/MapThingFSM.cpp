#include "MapThingFSM.h"



MapThingFSM::MapThingFSM(MapThing* thing)
{
	this->thing = thing;

}


MapThingFSM::~MapThingFSM()
{
	destroy_all_timers();
}


unsigned int MapThingFSM::get_id() {
	return thing->id;
}


void MapThingFSM::set_curr_timer_and_start(ALLEGRO_TIMER * new_curr_timer) {
	curr_timer = new_curr_timer;
	set_curr_timer_speed((*current_moving_iteration).second);
	al_start_timer(curr_timer);
}

void MapThingFSM::set_curr_timer_speed(double speed) {
	al_set_timer_speed(curr_timer, speed);
}
void MapThingFSM::stop_curr_timer() {
	al_stop_timer(curr_timer);
}

std::vector<ALLEGRO_TIMER*> MapThingFSM::get_all_timers() {
	return all_timers;
}

void MapThingFSM::create_timer(ALLEGRO_TIMER* timer) {
	timer = al_create_timer(1.0);
	all_timers.push_back(timer);
}
void MapThingFSM::destroy_all_timers() {
	for (std::vector<ALLEGRO_TIMER*>::iterator it = all_timers.begin(); it != all_timers.end(); ++it)
		al_destroy_timer(*it);
}

Direction_type MapThingFSM::get_current_action_direction()
{
	return (*current_moving_iteration).first;
}