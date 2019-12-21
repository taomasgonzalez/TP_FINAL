#include "ProyectilesActionsFSM.h"

void do_nothing_proy(void* data);

void start_moving_r(void* data);
void check_move_and_move(void* data);

void start_impacting_r(void* data);
void finished_impacting_r(void* data);


//void finish_falling_r(void* data);

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
	moving_state->push_back({ Event_type::END_OF_TABLE, moving_state, do_nothing_proy });

	impact_state->push_back({Event_type::DISAPPEARED, inactive_state, finished_impacting_r });
	impact_state->push_back({ Event_type::END_OF_TABLE, impact_state, do_nothing_proy});

	actual_state = moving_state;

	start_moving();
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
	if (!finished_logical_movement()) 
		continue_logical_movement();
	
	end_if_should_end_movement();
}

ALLEGRO_TIMER * ProyectilesActionsFSM::get_moving_timer()
{
	return moving_timer;
}
ALLEGRO_TIMER * ProyectilesActionsFSM::get_impacting_timer()
{
	return impacting_timer;
}
void ProyectilesActionsFSM::continue_logical_movement()
{
	obs_info.perform_logical_movement = true;
	notify_obs();
	obs_info.perform_logical_movement = false;
	++current_moving_iteration;
}

bool ProyectilesActionsFSM::finished_logical_movement() {
	return (current_moving_vector->end() == current_moving_iteration);
}

void ProyectilesActionsFSM::end_if_should_end_movement()
{
#pragma message("En algun lado hay que chequear directamente si deberia caer inmediatamente cuando me puse en iddle")
	obs_questions.should_interrupt_movement = true;
	notify_obs();
	obs_questions.should_interrupt_movement = false;
	if (obs_answers.should_interrupt_movement) {
		obs_info.interrupt_movement = true;
		notify_obs();
		obs_info.interrupt_movement = false;
	}
}

void ProyectilesActionsFSM::finished_impacting() {
	obs_info.interrupt_impact = true;
	notify_obs();						//ProyectileActionsFSMDRAWObserver
	obs_info.interrupt_impact = false;
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
void finished_impacting_r(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->finished_impacting();
}
void start_moving_r(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->start_moving();
}
