#include "PlayerActionsFSM.h"
#include "FSM_Class.h"

void do_nothing_player(void* data);


PlayerActionsFSM::PlayerActionsFSM(Userdata* data): FSM(data)
{
	std::vector<edge_t>* iddle_state = new std::vector<edge_t>();
	std::vector<edge_t>* walking_state = new std::vector<edge_t>();
	std::vector<edge_t>* jumping_state = new std::vector<edge_t>();
	std::vector<edge_t> * jumping_forward_state = new std::vector<edge_t>();
	std::vector<edge_t>* attacking_state = new std::vector<edge_t>();
	std::vector<edge_t>* falling_state = new std::vector<edge_t>();
	std::vector<edge_t>* pushing_state = new std::vector<edge_t>();
	std::vector<edge_t>* dead_state = new std::vector<edge_t>();

	/*
	walking_state->push_back({ Event_type::END_OF_TABLE, walking_state, do_nothing_player });

	iddle_state->push_back({Event_type::ATTACK, attacking_state, do_nothing_player});
	iddle_state->push_back({ Event_type::MOVE, iddle_state, analyze_movement);
	iddle_state->push_back({Event_type::WALKED, walking_state, start_walking_timers});
	iddle_state->push_back({ Event_type::DIED, dead_state, die });
	iddle_state->push_back({ Event_type::JUMPED_FORWARD, jumping_forward_state, start_jumping_forward_state_timers });
	//iddle_state->push_back({Event_type:: });
	*/

	this->actual_state = iddle_state;
}


PlayerActionsFSM::~PlayerActionsFSM()
{
}

void do_nothing_player(void * data) {

}