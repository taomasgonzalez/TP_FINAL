#pragma once
#include "AllegroClass.h"
#include "FSM_Class.h"
#include "MapThing.h"

class MapThingFSM : public FSM
{
public:
	MapThingFSM(MapThing * thing);
	~MapThingFSM();

	std::vector<ALLEGRO_TIMER*> get_all_timers();
	unsigned int get_id();
	Direction_type get_current_action_direction();

protected:

	typedef std::vector<std::pair<Direction_type, double>> process_t;

	void set_curr_timer_and_start(ALLEGRO_TIMER* new_curr_timer);
	void set_curr_timer_speed(double speed);
	void stop_curr_timer();

	process_t::iterator current_moving_iteration;
	process_t* current_moving_vector = NULL;
	ALLEGRO_TIMER* curr_timer = NULL;

	virtual void set_processes() = 0;
	virtual void create_all_timers() = 0;
	virtual void set_states() = 0;

	std::vector<ALLEGRO_TIMER*> all_timers;
	void create_timer(ALLEGRO_TIMER* timer);

	void destroy_all_timers();

private: 
	MapThing * thing = NULL;
};

