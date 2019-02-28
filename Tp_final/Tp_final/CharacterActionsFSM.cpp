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

void char_die(void* data);

void iddle_graph(void* data);

CharacterActionsFSM::CharacterActionsFSM(Character * character)
{
	this->character = character;

	std::vector<edge_t>* iddle_state = new std::vector<edge_t>();

	std::vector<edge_t>* walking_state = new std::vector<edge_t>();
	std::vector<edge_t>* jumping_state = new std::vector<edge_t>();
	std::vector<edge_t> * jumping_forward_state = new std::vector<edge_t>();
	std::vector<edge_t>* falling_state = new std::vector<edge_t>();

	std::vector<edge_t>* attacking_state = new std::vector<edge_t>();

	std::vector<edge_t>* dead_state = new std::vector<edge_t>();

	iddle_state->push_back({ Event_type::ATTACK, attacking_state, start_attacking_r});
	iddle_state->push_back({ Event_type::WALKED, walking_state, start_walking_r});
	iddle_state->push_back({ Event_type::JUMPED, jumping_state, start_jumping_r});
	iddle_state->push_back({ Event_type::JUMPED_FORWARD, jumping_forward_state, start_jumping_forward_r });
	iddle_state->push_back({Event_type::FELL, falling_state, start_falling_r});
	iddle_state->push_back({ Event_type::DIED, dead_state, char_die });
	iddle_state->push_back({ Event_type::END_OF_TABLE, iddle_state, do_nothing_char });

	walking_state->push_back({ Event_type::MOVE, walking_state, check_walking_and_walk});
	walking_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_walking});
	walking_state->push_back({ Event_type::DIED, dead_state, char_die });
	walking_state->push_back({ Event_type::END_OF_TABLE, walking_state, do_nothing_char });

	jumping_state->push_back({ Event_type::MOVE, jumping_state, check_jumping_and_jump });
	jumping_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_jumping });
	jumping_state->push_back({ Event_type::DIED, dead_state, char_die });
	jumping_state->push_back({ Event_type::END_OF_TABLE, jumping_state, do_nothing_char });

	jumping_forward_state->push_back({ Event_type::MOVE, jumping_state, check_jumping_forward_and_jump });
	jumping_forward_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_jumping_forward });
	jumping_forward_state->push_back({ Event_type::DIED, dead_state, char_die });
	jumping_forward_state->push_back({ Event_type::END_OF_TABLE, jumping_forward_state, do_nothing_char });

	falling_state->push_back({Event_type::MOVE, falling_state, check_fall_and_fall});
	falling_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_fall });
	falling_state->push_back({ Event_type::DIED, dead_state, char_die });
	falling_state->push_back({ Event_type::END_OF_TABLE, falling_state, do_nothing_char });

	attacking_state->push_back({Event_type::ATTACK, attacking_state, check_attack_and_attack});
	attacking_state->push_back({ Event_type::FINISHED_ATTACK, iddle_state, reset_attack });
	attacking_state->push_back({ Event_type::DIED, dead_state, char_die });
	attacking_state->push_back({ Event_type::END_OF_TABLE, attacking_state, do_nothing_char });

	dead_state->push_back({ Event_type::END_OF_TABLE, dead_state, do_nothing_char });

	this->actual_state = iddle_state;

	jumping_process.push_back(Direction_type::Jump_Straight);
	jumping_process.push_back(Direction_type::Jump_Straight);

	jumping_left_process.push_back(Direction_type::Jump_Straight);
	jumping_left_process.push_back(Direction_type::Jump_Straight);
	jumping_left_process.push_back(Direction_type::Left);

	jumping_right_process.push_back(Direction_type::Jump_Straight);
	jumping_right_process.push_back(Direction_type::Jump_Straight);
	jumping_right_process.push_back(Direction_type::Right);

	falling_process.push_back(Direction_type::Down);

	walking_left_process.push_back(Direction_type::Left);
	walking_right_process.push_back(Direction_type::Right);
}


CharacterActionsFSM::~CharacterActionsFSM()
{
	delete walking_state;
	delete jumping_state;
	delete jumping_forward_state;
	delete iddle_state;
	delete attacking_state;
	delete falling_state;
	delete dead_state;
}




void CharacterActionsFSM::kill_character() {
	character->die();
}

void CharacterActionsFSM::process_logical_movement()
{
	if (!finished_logical_movement())
		if (can_perform_logical_movement())
			continue_logical_movement();
		else
			interrupt_logical_movement();
}

void CharacterActionsFSM::process_logical_attack()
{
	if (!finished_logical_movement())
		if (can_perform_logical_movement())
			continue_logical_movement();
		else
			interrupt_logical_attack();
}

void CharacterActionsFSM::start_walking_timer()
{
}
void CharacterActionsFSM::start_jumping_timer()
{
}
void CharacterActionsFSM::start_jumping_forward_timer()
{
}
void CharacterActionsFSM::start_falling_timer()
{
}
void CharacterActionsFSM::start_attacking_timer()
{
}
void CharacterActionsFSM::start_jumping_forward()
{
	JUMPED_FORWARD_EventPackage * curr_jump = (JUMPED_FORWARD_EventPackage*) get_fsm_ev_pack();

	if (curr_jump->jumping_direction == Direction_type::Jump_Right){
		current_moving_iteration = jumping_right_process.begin();
		current_moving_vector = &jumping_right_process;
	}
	else if (curr_jump->jumping_direction == Direction_type::Jump_Left){
		current_moving_iteration = jumping_left_process.begin();
		current_moving_vector = &jumping_left_process;\
	}

	start_jumping_forward_timer();

}

void CharacterActionsFSM::start_attacking()
{
	start_attacking_timer();
}
void CharacterActionsFSM::start_falling() {
	start_falling_timer();
}

Direction_type CharacterActionsFSM::get_current_action_direction()
{
	return *current_moving_iteration;
}

unsigned int CharacterActionsFSM::get_character_id()
{
	return character->id;
}

void CharacterActionsFSM::continue_logical_movement()
{
	obs_info.perform_logical_movement = true;
	notify_obs();
	obs_info.perform_logical_movement = false;
	++current_moving_iteration;
}
void CharacterActionsFSM::continue_logical_attack() {
	obs_info.perform_logical_attack = true;
	notify_obs();
	obs_info.perform_logical_attack = false;
	++current_moving_iteration;
}
void CharacterActionsFSM::interrupt_logical_movement()
{
	obs_info.interrupt_movement = true;
	notify_obs();
	obs_info.interrupt_movement = false;
}

void CharacterActionsFSM::interrupt_logical_attack() {
	obs_info.interrupt_attack = true;
	notify_obs();
	obs_info.interrupt_attack = false;
}

void CharacterActionsFSM::start_walking()
{
	start_walking_timer();
}

void CharacterActionsFSM::start_jumping() {
	current_moving_iteration = jumping_process.begin();
	current_moving_vector = &jumping_process;
	start_jumping_timer();
}

bool CharacterActionsFSM::finished_logical_movement() {
	return (current_moving_vector->end() == current_moving_iteration);
}

bool CharacterActionsFSM::can_perform_logical_movement()
{
	this->obs_questions.can_perform_movement = true;
	notify_obs();
	this->obs_questions.can_perform_movement = false;
	return obs_answers.can_perform_movement;
}

void do_nothing_char(void * data) {

}

void start_walking_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*) data;
	(fsm->obs_info).start_walking_graph = true;
	fsm->notify_obs();
	(fsm->obs_info).start_walking_graph = false;
	fsm->start_walking();

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
	fsm->process_logical_attack();

}
void reset_attack(void* data) {
	iddle_graph(data);
}



void char_die(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->obs_info.dying_graph = true;
	fsm->notify_obs();
	fsm->obs_info.dying_graph = false;
	fsm->kill_character();
}


void iddle_graph(void * data)
{
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->obs_info.reset_graph = true;
	fsm->notify_obs();
	fsm->obs_info.reset_graph = false;
}


