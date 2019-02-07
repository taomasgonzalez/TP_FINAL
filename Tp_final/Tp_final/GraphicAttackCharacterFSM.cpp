#include "GraphicAttackCharacterFSM.h"
#include "GraphicAttackCharacterFSMRoutines.h"

GraphicAttackCharacterFSM::GraphicAttackCharacterFSM(Userdata*data): GraphicCharacterFSM(data)
{
	edge_t* attacking_state_aux = new edge_t[5];
	attacking_state = attacking_state_aux;
	edge_t attacking_state[6] =
	{
		{ Event_type::MOVE_TICKED, this->attacking_state,  move },
	{ Event_type::FINISHED_ATTACK, this->moving_state,  finish_attack },
	{ Event_type::DIED, this->moving_state, die },
	{ Event_type::DISAPPEARED, this->iddle_state, disappear },
	{ Event_type::END_OF_TABLE, this->attacking_state, do_nothing }
	};

	copy_event(attacking_state_aux, attacking_state, 5);
}


GraphicAttackCharacterFSM::~GraphicAttackCharacterFSM()
{
}
/*
GraphicAttackCharacterFSM::expand_state(edge_t* previous_state, int ,edge_t* additions, int number_of_additions) {
	for (int i = 0; i < number_of_additions; i++) {
		additions[i];
	}
}
*/
