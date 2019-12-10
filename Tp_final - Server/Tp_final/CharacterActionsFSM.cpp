#include "CharacterActionsFSM.h"
#include "Player.h"
#include "Enemy.h"

void do_nothing_char(void* data);

void start_walking_r(void* data);
void check_walking_and_walk(void* data);
void reset_walking(void* data);

void start_jumping_r(void* data);
void check_jumping_and_jump(void* data);
void reset_jumping(void* data);

void start_jumping_forward_r(void* data);
void check_jumping_forward_and_jump(void* data);
void reset_jumping_forward(void* data);

void start_falling_r(void* data);
void check_fall_and_fall(void* data);
void reset_fall(void* data);

void start_attacking_r(void* data);
void check_attack_and_attack(void* data);
void reset_attack(void* data);

void iddle_graph(void* data);

CharacterActionsFSM::CharacterActionsFSM(Character * character) : MapThingFSM(character)
{
	this->character = character;
	set_states();
	set_processes();
	create_all_timers();
	actual_state = iddle_state;
}


CharacterActionsFSM::~CharacterActionsFSM()
{
	destroy_all_timers();
	delete walking_state;
	delete jumping_state;
	delete jumping_forward_state;
	delete iddle_state;
	delete attacking_state;
	delete falling_state;
	delete dead_state;
}


void CharacterActionsFSM::set_processes() {

	jumping_process.push_back(std::make_pair(Direction_type::Jump_Straight, 0));
	jumping_process.push_back(std::make_pair(Direction_type::Jump_Straight, 0));

	jumping_left_process.push_back(std::make_pair(Direction_type::Jump_Straight,0));
	jumping_left_process.push_back(std::make_pair(Direction_type::Jump_Straight,0));
	jumping_left_process.push_back(std::make_pair(Direction_type::Left,0));

	jumping_right_process.push_back(std::make_pair(Direction_type::Jump_Straight, 0));
	jumping_right_process.push_back(std::make_pair(Direction_type::Jump_Straight, 0));
	jumping_right_process.push_back(std::make_pair(Direction_type::Right, 0));

	falling_process.push_back(std::make_pair(Direction_type::Down, 0));

	walking_left_process.push_back(std::make_pair(Direction_type::Left, 1/120.0));
	walking_right_process.push_back(std::make_pair(Direction_type::Right, 1 / 120.0));

}

void CharacterActionsFSM::create_all_timers() {
	
	create_timer(&attacking_timer);

}

void CharacterActionsFSM::set_states() {

	iddle_state = new std::vector<edge_t>();

	walking_state = new std::vector<edge_t>();
	jumping_state = new std::vector<edge_t>();
	jumping_forward_state = new std::vector<edge_t>();
	falling_state = new std::vector<edge_t>();

	attacking_state = new std::vector<edge_t>();

	dead_state = new std::vector<edge_t>();

	iddle_state->push_back({ Event_type::ATTACK, attacking_state, start_attacking_r });
	iddle_state->push_back({ Event_type::WALKED, walking_state, start_walking_r });
	iddle_state->push_back({ Event_type::JUMPED, jumping_state, start_jumping_r });
	iddle_state->push_back({ Event_type::FINISHED_GRAPH_STEP, iddle_state, do_nothing_char });
	iddle_state->push_back({ Event_type::END_OF_TABLE, iddle_state, do_nothing_char });

	iddle_state->push_back({ Event_type::JUMPED_FORWARD, jumping_forward_state, start_jumping_forward_r });
	iddle_state->push_back({ Event_type::FELL, falling_state, start_falling_r });
	iddle_state->push_back({ Event_type::END_OF_TABLE, iddle_state, do_nothing_char });

	walking_state->push_back({ Event_type::FINISHED_GRAPH_STEP, walking_state, check_walking_and_walk });
	walking_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_walking });
	walking_state->push_back({ Event_type::WALKED, walking_state, do_nothing_char });
	walking_state->push_back({ Event_type::END_OF_TABLE, walking_state, do_nothing_char });

	jumping_state->push_back({ Event_type::MOVE, jumping_state, check_jumping_and_jump });
	jumping_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_jumping });
	jumping_state->push_back({ Event_type::END_OF_TABLE, jumping_state, do_nothing_char });

	jumping_forward_state->push_back({ Event_type::MOVE, jumping_forward_state, check_jumping_forward_and_jump });
	jumping_forward_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_jumping_forward });
	jumping_forward_state->push_back({ Event_type::END_OF_TABLE, jumping_forward_state, do_nothing_char });

	falling_state->push_back({ Event_type::MOVE, falling_state, check_fall_and_fall });
	falling_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_fall });
	falling_state->push_back({ Event_type::END_OF_TABLE, falling_state, do_nothing_char });

	attacking_state->push_back({ Event_type::ATTACK, attacking_state, check_attack_and_attack });
	attacking_state->push_back({ Event_type::FINISHED_ATTACK, iddle_state, reset_attack });
	attacking_state->push_back({ Event_type::END_OF_TABLE, attacking_state, do_nothing_char });

	dead_state->push_back({ Event_type::END_OF_TABLE, dead_state, do_nothing_char });

}

void CharacterActionsFSM::kill_character() {
	character->die();
}

void CharacterActionsFSM::process_logical_movement()
{
	
	if(!finished_logical_movement()){			//do i have any more sub-movements to perform?
		if (can_perform_logical_movement())		//can i perform this sub-movement? Do the game conditions enable me to do so?
			continue_logical_movement();		//if so, perform the movement.
		else {

		}
	}
	//appends a movement finished event to the queue if the graphic part has finished its sequence. 
	end_if_should_end_movement();
	
}

void CharacterActionsFSM::process_logical_attack(){
	if (!has_attacked()) 
		attack();

	end_if_should_end_attack();
}

void CharacterActionsFSM::start_jumping_forward(){
	JUMPED_FORWARD_EventPackage * curr_jump = (JUMPED_FORWARD_EventPackage*) get_fsm_ev_pack();

	if (curr_jump->jumping_direction == Direction_type::Jump_Right)
		set_curr_process(&jumping_right_process);
	else if (curr_jump->jumping_direction == Direction_type::Jump_Left)
		set_curr_process(&jumping_left_process);

	//set_curr_timer_and_start(jumping_forward_timer);

}

void CharacterActionsFSM::start_attacking(){
	attacked = false;
	set_curr_timer_and_start(attacking_timer);
}
void CharacterActionsFSM::start_falling() {

	set_curr_process(&falling_process);
	//set_curr_timer_and_start(falling_timer);

}

void CharacterActionsFSM::stop_action(){
	stop_curr_timer();
}

ALLEGRO_TIMER * CharacterActionsFSM::get_attacking_timer(){
	return attacking_timer;
}
void CharacterActionsFSM::continue_logical_movement(){

	obs_info.perform_logical_movement = true;
	notify_obs();						//CharacterSceneObserver
	obs_info.perform_logical_movement = false;

	++current_moving_iteration;
}



void CharacterActionsFSM::start_jumping() {
	set_curr_process(&jumping_process);
}

void CharacterActionsFSM::end_if_should_end_movement(){
	#pragma message("En algun lado hay que chequear directamente si deberia caer inmediatamente cuando me puse en iddle")
	obs_questions.should_interrupt_movement = true;
	notify_obs();						//PlayerActionsFSMDRAWObserver
	obs_questions.should_interrupt_movement = false;

	if (obs_answers.should_interrupt_movement) {
		obs_info.interrupt_movement = true;
		notify_obs();				
		obs_info.interrupt_movement = false;
		stop_curr_timer();
	}
}

void CharacterActionsFSM::end_if_should_end_attack(){
	obs_questions.should_interrupt_attack = true;
	notify_obs();
	obs_questions.should_interrupt_attack = false;

	if (obs_answers.should_interrupt_attack) {
		obs_info.interrupt_attack = true;
		notify_obs();
		obs_info.interrupt_attack = false;
		stop_curr_timer();
	}
}

bool CharacterActionsFSM::finished_logical_movement() {
	return (current_moving_vector->end() == current_moving_iteration);
}

bool CharacterActionsFSM::can_perform_logical_movement(){

	#pragma message("Germo tiene que verificar si se puede ejecutar este movimiento desde escena. Este observer es CharacterSceneObserver")
	obs_questions.can_perform_movement = true;
	notify_obs();				//CharacterSceneObserver
	#pragma message("Debería editar obs_answers.can_perform_movement desde escena?")

	this->obs_questions.can_perform_movement = false;
	return obs_answers.can_perform_movement;
}

bool CharacterActionsFSM::has_attacked() {
	return attacked;
}
void CharacterActionsFSM::attack() {

	obs_info.perform_logical_attack = true;
	notify_obs();
	obs_info.perform_logical_attack = false;

	//to prevent other attack timers from being executed.
	attacked = true;
}

void do_nothing_char(void * data) {

}

void start_walking_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*) data;
	fsm->start_walking();
}

void CharacterActionsFSM::start_walking() {
	WALKED_EventPackage * curr_walk = (WALKED_EventPackage*)get_fsm_ev_pack();
	
	if (curr_walk->walking_direction == Direction_type::Right)
		set_curr_process(&walking_right_process);
	else if (curr_walk->walking_direction == Direction_type::Left)
		set_curr_process(&walking_left_process);

	set_fsm_ev_pack(new MOVE_EventPackage(curr_walk->walking_direction));

	if (can_perform_logical_movement()) {
		obs_info.start_walking_graph = true;
		notify_obs();
		obs_info.start_walking_graph = false;
	}
}
void check_walking_and_walk(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->process_logical_movement();
}
void reset_walking(void* data) {
	iddle_graph(data);
}

void start_jumping_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	(fsm->obs_info).start_jumping_graph = true;
	fsm->notify_obs();
	(fsm->obs_info).start_jumping_graph = false;

	fsm->start_jumping();
}
void check_jumping_and_jump(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->process_logical_movement();
	
}
void reset_jumping(void* data) {
	iddle_graph(data);
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->stop_action();
}

void start_jumping_forward_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->obs_info.start_jumping_forward_graph = true;
	fsm->notify_obs();
	fsm->obs_info.start_jumping_forward_graph = false;

	fsm->start_jumping_forward();
}
void check_jumping_forward_and_jump(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->process_logical_movement();

}
void reset_jumping_forward(void* data) {
	iddle_graph(data);
}

void start_falling_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->obs_info.start_falling_graph = true;
	fsm->notify_obs();
	fsm->obs_info.start_falling_graph = false;
	fsm->start_falling();

}
void check_fall_and_fall(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->process_logical_movement();
}
void reset_fall(void* data) {
	iddle_graph(data);

}

void start_attacking_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->obs_info.start_attacking_graph = true;
	fsm->notify_obs();
	fsm->obs_info.start_attacking_graph = false;
	fsm->start_attacking();

}

void check_attack_and_attack(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->start_attacking();
}

void reset_attack(void* data) {
	iddle_graph(data);
}

void iddle_graph(void * data)
{
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->obs_info.reset_graph = true;
	fsm->notify_obs();
	fsm->obs_info.reset_graph = false;
}
