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

	struct observer_info {
		bool start_moving_graph = false;
		bool start_impacting_graph = false;
		bool start_falling_graph = false;

	};

	observer_info obs_info;

	void start_impacting();
	void start_moving();
	void start_falling();

	void process_logical_movement();
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
	ALLEGRO_TIMER* impacting_timer = NULL;

	process_t moving_right_process;
	process_t moving_left_process;
	process_t falling_process;


};

