#include "CharacterActionsFSM.h"

void do_nothing_player(void* data);

void start_pushing(void* data);

void start_walking(void* data);
void check_walking_and_walk(void* data);
void reset_walking(void* data);

void start_jumping(void* data);
void check_jumping_and_jump(void* data);
void reset_jumping(void* data);

void start_jumping_forward(void* data);
void check_jumping_forward_and_jump(void* data);
void reset_jumping_forward(void* data);

void start_falling(void* data);
void check_fall_and_fall(void* data);
void reset_fall(void* data);

void start_attacking(void* data);
void check_attack_and_attack(void* data);
void reset_attack(void* data);

void check_push_and_push(void* data);
void reset_push(void* data);

void char_die(void* data);
void char_revive(void* data);


CharacterActionsFSM::CharacterActionsFSM(): FSM()
{
	std::vector<edge_t>* iddle_state = new std::vector<edge_t>();

	std::vector<edge_t>* walking_state = new std::vector<edge_t>();
	std::vector<edge_t>* jumping_state = new std::vector<edge_t>();
	std::vector<edge_t> * jumping_forward_state = new std::vector<edge_t>();
	std::vector<edge_t>* falling_state = new std::vector<edge_t>();
	std::vector<edge_t>* pushing_state = new std::vector<edge_t>();

	std::vector<edge_t>* attacking_state = new std::vector<edge_t>();

	std::vector<edge_t>* dead_state = new std::vector<edge_t>();

	iddle_state->push_back({ Event_type::ATTACK, attacking_state, start_attacking});
	iddle_state->push_back({ Event_type::WALKED, walking_state, start_walking});
	iddle_state->push_back({ Event_type::JUMPED, jumping_state, start_jumping});
	iddle_state->push_back({ Event_type::JUMPED_FORWARD, jumping_forward_state, start_jumping_forward });
	iddle_state->push_back({Event_type::FELL, falling_state, start_falling});
	iddle_state->push_back({ Event_type::PUSHED, pushing_state, start_pushing });
	iddle_state->push_back({ Event_type::DIED, dead_state, char_die });

	walking_state->push_back({ Event_type::MOVE, walking_state, check_walking_and_walk});
	walking_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_walking});
	walking_state->push_back({ Event_type::DIED, dead_state, char_die });

	jumping_state->push_back({ Event_type::MOVE, jumping_state, check_jumping_and_jump });
	jumping_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_jumping });
	jumping_state->push_back({ Event_type::DIED, dead_state, char_die });

	jumping_forward_state->push_back({ Event_type::MOVE, jumping_state, check_jumping_forward_and_jump });
	jumping_forward_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_jumping_forward });
	jumping_forward_state->push_back({ Event_type::DIED, dead_state, char_die });

	falling_state->push_back({Event_type::MOVE, falling_state, check_fall_and_fall});
	falling_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_fall });
	falling_state->push_back({ Event_type::DIED, dead_state, char_die });

	pushing_state->push_back({ Event_type::MOVE, pushing_state, check_push_and_push });
	pushing_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_push });
	pushing_state->push_back({ Event_type::DIED, dead_state, char_die });

	attacking_state->push_back({Event_type::ATTACK, attacking_state, check_attack_and_attack});
	attacking_state->push_back({ Event_type::FINISHED_ATTACK, iddle_state, reset_attack });
	attacking_state->push_back({ Event_type::DIED, dead_state, char_die });

	dead_state->push_back({ Event_type::APPEARED, iddle_state, char_revive });

	this->actual_state = iddle_state;
}


CharacterActionsFSM::~CharacterActionsFSM()
{
	delete walking_state;
	delete jumping_state;
	delete jumping_forward_state;
	delete iddle_state;
	delete attacking_state;
	delete falling_state;
	delete pushing_state;
	delete dying_state;
}

void do_nothing_player(void * data) {

}



void start_pushing(void* data) {

}

void start_walking(void* data) {

}
void check_walking_and_walk(void* data) {

}
void reset_walking(void* data) {

}

void start_jumping(void* data) {

}
void check_jumping_and_jump(void* data) {

}
void reset_jumping(void* data) {

}

void start_jumping_forward(void* data) {

}
void check_jumping_forward_and_jump(void* data) {

}
void reset_jumping_forward(void* data) {

}

void start_falling(void* data) {

}
void check_fall_and_fall(void* data) {

}
void reset_fall(void* data) {

}

void start_attacking(void* data) {

}
void check_attack_and_attack(void* data) {

}
void reset_attack(void* data) {

}

void check_push_and_push(void* data) {

}
void reset_push(void* data) {

}

void char_die(void* data) {

}
void char_revive(void* data) {

}

