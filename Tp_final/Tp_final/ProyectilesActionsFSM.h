#pragma once
#include "Proyectile.h"
#include "MapThingFSM.h"

class ProyectilesActionsFSM : public MapThingFSM
{
public:
	ProyectilesActionsFSM(Proyectile* proyectile);
	~ProyectilesActionsFSM();

	struct obs_info{
		bool move = false;
		bool impact = false;
		bool fall = false;
	};

	obs_info observer_info;

	Direction_type get_direction();
	void impact();
	void start_moving();
	void start_falling();

protected:

	std::vector<edge_t>* moving_state = NULL;
	std::vector<edge_t>* impact_state = NULL;
	std::vector<edge_t>* inactive_state = NULL;
	std::vector<edge_t>* falling_state = NULL;

	void create_all_timers();
	void set_states();
	void set_processes();

private:

	Proyectile * proyectile = NULL;

	ALLEGRO_TIMER* moving_timer = NULL;
	ALLEGRO_TIMER* falling_timer = NULL;

	process_t moving_right_process;
	process_t moving_left_process;
	process_t falling_process;

	//void process_logical_movement();
};

