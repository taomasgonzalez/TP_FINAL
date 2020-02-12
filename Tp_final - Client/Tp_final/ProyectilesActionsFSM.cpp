#include "ProyectilesActionsFSM.h"

void do_nothing_proy(void* data);

void start_moving_r(void* data);
void check_move_and_move(void* data);

void start_impacting_r(void* data);

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
}

void ProyectilesActionsFSM::set_processes() {

	moving_left_process.push_back(std::make_pair(Direction_type::Left, 0));
	moving_left_process.push_back(std::make_pair(Direction_type::Left, 0));
	moving_left_process.push_back(std::make_pair(Direction_type::Left, 0));

	moving_right_process.push_back(std::make_pair(Direction_type::Right, 0));
	moving_right_process.push_back(std::make_pair(Direction_type::Right, 0));
	moving_right_process.push_back(std::make_pair(Direction_type::Right, 0));

}

void ProyectilesActionsFSM::set_states() {

	moving_state = new std::vector<edge_t>();
	impact_state = new std::vector<edge_t>();
	inactive_state = new std::vector<edge_t>();

	inactive_state->push_back({ Event_type::END_OF_TABLE, inactive_state, do_nothing_proy });

	moving_state->push_back({ Event_type::FINISHED_GRAPH_STEP, moving_state, check_move_and_move });
	moving_state->push_back({ Event_type::GOT_HIT, impact_state, start_impacting_r });
	moving_state->push_back({ Event_type::FINISHED_MOVEMENT, inactive_state, do_nothing_proy });
	moving_state->push_back({ Event_type::END_OF_TABLE, moving_state, do_nothing_proy });

	impact_state->push_back({Event_type::FINISHED_GRAPH_STEP, inactive_state, do_nothing_proy });
	impact_state->push_back({ Event_type::END_OF_TABLE, impact_state, do_nothing_proy});

	actual_state = moving_state;

	start_moving();
	notify_obs();
}

void ProyectilesActionsFSM::create_all_timers() {
}
void ProyectilesActionsFSM::start_moving() {

	Sense_type sense = proyectile->get_sense();
	
	if (sense == Sense_type::Left)
		set_curr_process(&moving_left_process);
	else if(sense == Sense_type::Right)
		set_curr_process(&moving_right_process);

	obs_info.start_moving_graph = true;
	notify_obs();								//ProyectilesActionsFSMDRAWObserver
	obs_info.start_moving_graph = false;
}

void ProyectilesActionsFSM::start_impacting() {
	
	obs_info.start_impacting_graph = true;
	notify_obs();								//ProyectilesActionsFSMDRAWObserver
	obs_info.start_impacting_graph = false;
}


void ProyectilesActionsFSM::process_logical_movement()
{
	bool can_perform = true;
	if (!finished_logical_movement()) {			//do i have any more sub-movements to perform?

		//can i perform this sub-movement? Do the game conditions enable me to do so?
		if (!first_logical_movement())
			can_perform = can_perform_logical_movement();
		if (can_perform)
			continue_logical_movement();
	}

	if (can_perform && !finished_logical_movement()) {
		obs_info.start_moving_graph = true;
		notify_obs();								//ProyectilesActionsFSMDRAWObserver
		obs_info.start_moving_graph = false;
	}
	else 
		interrupt_move();
}



void ProyectilesActionsFSM::continue_logical_movement()
{
	obs_info.perform_logical_movement = true;
	notify_obs();
	obs_info.perform_logical_movement = false;
	++current_moving_iteration;
}

bool ProyectilesActionsFSM::finished_logical_movement() {
	if(current_moving_vector != NULL)
		return (current_moving_vector->end() == current_moving_iteration);
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
void start_moving_r(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->start_moving();
}
bool ProyectilesActionsFSM::first_logical_movement() {
	if(current_moving_vector != NULL)
		return current_moving_vector->begin() == current_moving_iteration;
}

bool ProyectilesActionsFSM::can_perform_logical_movement() {
	obs_questions.can_perform_movement = true;
	notify_obs();				//ProyectilesSceneObserver
	obs_questions.can_perform_movement = false;
	return obs_answers.can_perform_movement;
}

bool ProyectilesActionsFSM::has_disappeared() {
	return actual_state == inactive_state;
}

void ProyectilesActionsFSM::interrupt_move() {
	obs_info.interrupt_movement = true;		//append a movement finished event to the queue.
	notify_obs();
	obs_info.interrupt_movement = false;
}


void ProyectilesActionsFSM::print_curr_state() {
	if (moving_state == actual_state)
		cout << "moving_state" << endl;
	else if (inactive_state == actual_state)
		cout << "inactive_state" << endl;
	else if (impact_state == actual_state)
		cout << "impact_state" << endl;
}
