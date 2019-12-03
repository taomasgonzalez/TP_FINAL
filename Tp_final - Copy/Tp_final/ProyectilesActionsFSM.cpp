#include "ProyectilesActionsFSM.h"

void do_nothing_proy(void* data);

void start_moving_r(void* data);
void check_move_and_move(void* data);

void start_impacting_r(void* data);
void finished_impacting_r(void* data);

void start_falling_pr(void* data);
void check_fall_and_fall_r(void* data);

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
	delete falling_state;
}

void ProyectilesActionsFSM::set_processes() {

	moving_left_process.push_back(std::make_pair(Direction_type::Left, 0));
	moving_left_process.push_back(std::make_pair(Direction_type::Left, 0));
	moving_left_process.push_back(std::make_pair(Direction_type::Left, 0));

	moving_right_process.push_back(std::make_pair(Direction_type::Right, 0));
	moving_right_process.push_back(std::make_pair(Direction_type::Right, 0));
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

	impact_state->push_back({Event_type::DISAPPEARED, inactive_state, finished_impacting_r });
	impact_state->push_back({ Event_type::END_OF_TABLE, impact_state, do_nothing_proy});

	falling_state->push_back({ Event_type::FELL, falling_state, start_falling_pr });
	falling_state->push_back({ Event_type::MOVE, falling_state, check_fall_and_fall_r });
	falling_state->push_back({ Event_type::FINISHED_MOVEMENT, impact_state, start_impacting_r});
	falling_state->push_back({ Event_type::END_OF_TABLE, falling_state, do_nothing_proy });

	start_moving();

	actual_state = moving_state;

}

void ProyectilesActionsFSM::create_all_timers() {
	create_timer(&moving_timer);
	create_timer(&falling_timer);
}
void ProyectilesActionsFSM::start_moving() {

	obs_info.start_moving_graph = true;
	notify_obs();								//ProyectilesActionsFSMDRAWObserver
	obs_info.start_moving_graph = false;

	MOVE_EventPackage* ev_pack = static_cast<MOVE_EventPackage*>(get_fsm_ev_pack());
	Direction_type direction = ev_pack->give_me_your_direction();
	
	if (direction == Direction_type::Left) 
		set_curr_process(&moving_left_process);
	else if(direction == Direction_type::Right) 
		set_curr_process(&moving_right_process);

	set_curr_timer_and_start(moving_timer);
}

void ProyectilesActionsFSM::start_impacting() {
	
	obs_info.start_impacting_graph = true;
	notify_obs();								//ProyectilesActionsFSMDRAWObserver
	obs_info.start_impacting_graph = false;

	set_curr_timer_and_start(impacting_timer);
}

void ProyectilesActionsFSM::start_falling() {

	obs_info.start_falling_graph = true;
	notify_obs();								//ProyectilesActionsFSMDRAWObserver
	obs_info.start_falling_graph = false;

	set_curr_process(&falling_process);
	set_curr_timer_and_start(falling_timer);
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
ALLEGRO_TIMER * ProyectilesActionsFSM::get_falling_timer()
{
	return falling_timer;
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
	if (!finished_logical_movement())
		set_curr_timer_speed((*current_moving_iteration).second);
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
		stop_curr_timer();
	}
}

void ProyectilesActionsFSM::finished_impacting() {
	obs_info.interrupt_impact = true;
	notify_obs();						//ProyectileActionsFSMDRAWObserver
	obs_info.interrupt_impact = false;

	//delete from scene???
}

void do_nothing_proy(void* data) {

}
void check_move_and_move(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->process_logical_movement();
}
void check_fall_and_fall_r(void* data) {
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
void start_falling_pr(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->start_falling();
}
