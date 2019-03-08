#include "ProyectilesActionsFSM.h"

void do_nothing_proy(void* data);

void start_moving_r(void* data);
void check_move_and_move(void* data);

void start_impacting_r(void* data);
void finished_impacting(void* data);

void start_falling_pr(void* data);


ProyectilesActionsFSM::ProyectilesActionsFSM(Proyectile* proyectile): MapThingFSM(proyectile)
{
	this->proyectile = proyectile;

	set_processes();
	set_states();
	create_all_timers();

	this->actual_state = moving_state;
}


ProyectilesActionsFSM::~ProyectilesActionsFSM()
{
	//the parent class automatically destroys all timers!! 

	delete moving_state;
	delete impact_state;
	delete inactive_state;
	delete falling_state;
}

void ProyectilesActionsFSM::set_processes() {

	moving_left_process.push_back(std::make_pair(Direction_type::Left, 0));

	moving_right_process.push_back(std::make_pair(Direction_type::Right, 0));

	falling_process.push_back(std::make_pair(Direction_type::Down, 0));

}

void ProyectilesActionsFSM::set_states() {

	moving_state = new std::vector<edge_t>();
	impact_state = new std::vector<edge_t>();
	inactive_state = new std::vector<edge_t>();
	falling_state = new std::vector<edge_t>();

	inactive_state->push_back({ Event_type::END_OF_TABLE, inactive_state, do_nothing_proy});

	moving_state->push_back({ Event_type::MOVE, moving_state, check_move_and_move });
	moving_state->push_back({ Event_type::GOT_HIT, impact_state, start_impacting_r });
	moving_state->push_back({ Event_type::END_OF_TABLE, moving_state, do_nothing_proy });

	impact_state->push_back({Event_type::DISAPPEARED, inactive_state, finished_impacting});
	impact_state->push_back({ Event_type::END_OF_TABLE, impact_state, do_nothing_proy});

	falling_state->push_back({ Event_type::FELL, falling_state, start_falling_pr });
	falling_state->push_back({ Event_type::END_OF_TABLE, falling_state, do_nothing_proy });

	start_moving();

	actual_state = moving_state;

}

void ProyectilesActionsFSM::create_all_timers() {
	create_timer(moving_timer);
	create_timer(falling_timer);
}
void ProyectilesActionsFSM::start_moving() {

	MOVE_EventPackage* ev_pack = static_cast<MOVE_EventPackage*>(get_fsm_ev_pack());
	Direction_type direction = ev_pack->give_me_your_direction();

	if (direction == Direction_type::Left) 
		set_curr_process(&moving_left_process);
	else if(direction == Direction_type::Right) 
		set_curr_process(&moving_right_process);

	set_curr_timer_and_start(moving_timer);
}

void ProyectilesActionsFSM::start_impacting() {
	
	set_curr_timer_and_start(impacting_timer);
}

void ProyectilesActionsFSM::start_falling() {

}

void ProyectilesActionsFSM::process_logical_movement()
{

	/*
	if (!finished_logical_movement()) {
		if (can_perform_logical_movement())
			continue_logical_movement();
	}
	end_if_should_end_movement();
	*/
}

void do_nothing_proy(void* data) {

}


void check_move_and_move(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->process_logical_movement();
}

void start_impacting_r(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->start_impacting();
}

void finished_impacting(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;

}

void start_moving_r(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->obs_info.start_moving_graph = true;
	fsm->notify_obs();
	fsm->obs_info.start_moving_graph = false;

	fsm->start_moving();
}

void start_falling_pr(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->start_falling();
}