#pragma once
#include "Proyectile.h"
#include "MapThingFSM.h"

class ProyectilesActionsFSM : public MapThingFSM
{
public:
	ProyectilesActionsFSM(Proyectile* proyectile);
	~ProyectilesActionsFSM();

	struct observer_info {
		bool start_moving_graph = false;
		bool start_impacting_graph = false;
		bool start_falling_graph = false;
		bool perform_logical_movement = false;
		bool interrupt_movement = false;
		bool interrupt_impact = false;
	};

	observer_info obs_info;

	struct observer_QA {
		bool can_perform_movement = false;
		bool should_interrupt_movement = false;
	};
	observer_QA obs_questions;
	observer_QA obs_answers;


	void start_impacting();
	void start_moving();

	void process_logical_movement();

	bool has_disappeared();
protected:

	std::vector<edge_t>* moving_state = NULL;
	std::vector<edge_t>* impact_state = NULL;
	std::vector<edge_t>* inactive_state = NULL;

	void create_all_timers();
	void set_states();
	void set_processes();

private:

	Proyectile * proyectile = NULL;

	process_t moving_right_process;
	process_t moving_left_process;

	void continue_logical_movement();
	bool finished_logical_movement();
	bool can_perform_logical_movement();
	bool first_logical_movement();
	void interrupt_move();
	void print_curr_state();
};

