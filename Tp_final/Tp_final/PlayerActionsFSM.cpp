#include "PlayerActionsFSM.h"

void player_revive(void* data);
void start_pushing(void* data);

void check_push_and_push(void* data);
void reset_push(void* data);
void iddle_graph_player(void* data);
void player_die(void*data);

PlayerActionsFSM::PlayerActionsFSM(Player* player): CharacterActionsFSM(player)
{
	this->player = player;

	std::vector<edge_t>* pushing_state = new std::vector<edge_t>();

	expand_state(iddle_state, { Event_type::PUSHED, pushing_state, start_pushing });
	expand_state(iddle_state, { Event_type::DIED, dead_state, player_die });

	expand_state(walking_state, { Event_type::DIED, dead_state, player_die });
	expand_state(jumping_state, { Event_type::DIED, dead_state, player_die });
	expand_state(jumping_forward_state, { Event_type::DIED, dead_state, player_die });
	expand_state(falling_state, { Event_type::DIED, dead_state, player_die });
	expand_state(attacking_state, { Event_type::DIED, dead_state, player_die });

	expand_state(dead_state, { Event_type::APPEARED, iddle_state, player_revive });

	pushing_state->push_back({ Event_type::MOVE, pushing_state, check_push_and_push });
	pushing_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_push });
	pushing_state->push_back({ Event_type::DIED, dead_state, get_routine(iddle_state,Event_type::DIED) });

}


PlayerActionsFSM::~PlayerActionsFSM()
{
	delete pushing_state;
}
void player_revive(void* data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	iddle_graph_player(data);
	fsm->revive_player();
}
void PlayerActionsFSM::start_pushing_timer()
{
}
void PlayerActionsFSM::revive_player() {
	player->revive();
}

void player_die(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->obs_info.dying_graph = true;
	fsm->notify_obs();
	fsm->obs_info.dying_graph = false;
	fsm->kill_character();
}

void start_pushing(void* data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	(fsm->obs_info).start_pushing_graph = true;
	fsm->notify_obs();
	(fsm->obs_info).start_pushing_graph = false;

	fsm->start_pushing_timer();
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

