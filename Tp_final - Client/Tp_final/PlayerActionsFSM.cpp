#include "PlayerActionsFSM.h"

void player_revive(void* data);
void start_pushing_r(void* data);

void check_push_and_push(void* data);
void reset_push(void* data);
void iddle_graph_player(void* data);
void player_die(void*data);
void do_nothing_player_r(void* data);

void do_nothing_player_r(void* data) {

}


PlayerActionsFSM::PlayerActionsFSM(Player* player): CharacterActionsFSM(player)
{
	this->player = player;

	set_states();
	set_processes();
	create_all_timers();

	this->actual_state = iddle_state;
}

PlayerActionsFSM::~PlayerActionsFSM()
{
	delete pushing_state;
}
void PlayerActionsFSM::revive_player() {
	player->revive();
}
void PlayerActionsFSM::set_states() {

	pushing_state = new std::vector<edge_t>();

	expand_state(iddle_state, { Event_type::PUSHED, pushing_state, start_pushing_r });
	expand_state(iddle_state, { Event_type::DIED, dead_state, player_die });

	expand_state(walking_state, { Event_type::DIED, dead_state, player_die });
	expand_state(jumping_state, { Event_type::DIED, dead_state, player_die });
	expand_state(jumping_forward_state, { Event_type::DIED, dead_state, player_die });
	expand_state(falling_state, { Event_type::DIED, dead_state, player_die });
	expand_state(attacking_state, { Event_type::DIED, dead_state, player_die });

	pushing_state->push_back({ Event_type::MOVE, pushing_state, check_push_and_push });
	pushing_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_push });
	pushing_state->push_back({ Event_type::DIED, dead_state, get_routine(iddle_state,Event_type::DIED) });
	pushing_state->push_back({ Event_type::END_OF_TABLE, dead_state, do_nothing_player_r });


	expand_state(dead_state, { Event_type::APPEARED, iddle_state, player_revive });
}

void PlayerActionsFSM::create_all_timers() {
}

void PlayerActionsFSM::set_processes() {

	pushing_right_process.push_back(std::make_pair(Direction_type::Right, 0));

	pushing_left_process.push_back(std::make_pair(Direction_type::Left, 0));
}


void PlayerActionsFSM::start_pushing() {
	obs_info.start_pushing_graph = true;
	notify_obs();
	obs_info.start_pushing_graph = false;

	PUSHED_EventPackage * curr_push = (PUSHED_EventPackage*)get_fsm_ev_pack();

	if (curr_push->pushing_direction == Direction_type::Jump_Right) 
		set_curr_process(&pushing_right_process);
	else if (curr_push->pushing_direction == Direction_type::Jump_Left) 
		set_curr_process(&pushing_left_process);

}

void player_revive(void* data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	iddle_graph_player(data);
	fsm->revive_player();
}

void player_die(void* data) {

	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	fsm->kill_player();

}

void PlayerActionsFSM::kill_player() {

	obs_info.dying_graph = true;
	notify_obs();
	obs_info.dying_graph = false;

	player->die();
}
void start_pushing_r(void* data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	fsm->start_pushing();
}

void check_push_and_push(void* data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	
}
void reset_push(void* data) {
	iddle_graph_player(data);
}

void iddle_graph_player(void *data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	fsm->obs_info.reset_graph = true;
	fsm->notify_obs();
	fsm->obs_info.reset_graph = false;
}



