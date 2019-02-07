#include "GraphicAttackCharacterFSM.h"
#include "GraphicAttackCharacterFSMRoutines.h"

GraphicAttackCharacterFSM::GraphicAttackCharacterFSM(Userdata*data): GraphicCharacterFSM(data)
{
	attacking_state = new std::vector<edge_t>();
	attacking_state->push_back({ Event_type::MOVE_TICKED, this->attacking_state,  move });
	attacking_state->push_back({ Event_type::FINISHED_ATTACK, this->moving_state,  finish_attack });
	attacking_state->push_back({ Event_type::DIED, this->moving_state, die });
	attacking_state->push_back({ Event_type::DISAPPEARED, this->iddle_state, disappear });
	attacking_state->push_back({ Event_type::END_OF_TABLE, this->attacking_state, do_nothing });

	expand_state(moving_state, { Event_type::ATTACKED, attacking_state,  attack });
}


GraphicAttackCharacterFSM::~GraphicAttackCharacterFSM()
{
	delete attacking_state;
}

