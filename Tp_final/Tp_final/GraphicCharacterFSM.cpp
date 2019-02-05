#include "GraphicCharacterFSM.h"

void do_nothing(void* data);
void disappear(void* data);
void attack(void* data);
void move(void* data);

GraphicCharacterFSM::GraphicCharacterFSM(Userdata* data) : FSM(data)
{
	edge_t* moving_state_aux = new edge_t[6];
	moving_state = moving_state_aux;

	edge_t moving_state[6] =
	{
		{ Event_type::MOVE_TICKED, this->impacting_state, move },
	{ Event_type::ATTACKED, this->attacking_state,  attack},
	{ Event_type::DISAPPEARED, this->moving_state, disappear },
	{ Event_type::END_OF_TABLE, this->moving_state, do_nothing }
	};

	copy_event(moving_state_aux, moving_state, 6);

	edge_t* attacking_state_aux = new edge_t[5];
	attacking_state = attacking_state_aux;

	copy_event(attacking_state_aux, attacking_state, 5);

}




GraphicCharacterFSM::~GraphicCharacterFSM()
{
}


void do_nothing(void* data) {

}
void disappear(void* data) {
	GraphicCharacterFSM* fsm = (GraphicCharacterFSM*)data;
	fsm->should_disappear = true;
	fsm->notify_obs();
	fsm->should_disappear= false;
}
void attack(void* data) {
	GraphicCharacterFSM* fsm = (GraphicCharacterFSM*)data;
	fsm->should_attack = true;
	fsm->notify_obs();
	fsm->should_attack = false;
}
void move(void* data) {
	GraphicCharacterFSM* fsm = (GraphicCharacterFSM*)data;
	fsm->should_move = true;
	fsm->notify_obs();
	fsm->should_move = false;
}

