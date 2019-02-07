#include "GraphicCharacterFSM.h"
#include "GraphicCharacterFSMRoutines.h"


GraphicCharacterFSM::GraphicCharacterFSM(Userdata* data) : FSM(data)
{
	edge_t* moving_state_aux = new edge_t[6];
	moving_state = moving_state_aux;

	edge_t moving_state[6] =
	{
	{ Event_type::MOVE_TICKED, this->moving_state, move },
	{ Event_type::ATTACKED, this->attacking_state,  attack},
	{ Event_type::DIED, this->moving_state, die }
	{ Event_type::DISAPPEARED, this->iddle_state, disappear },
	{ Event_type::END_OF_TABLE, this->moving_state, do_nothing }
	};

	copy_event(moving_state_aux, moving_state, 6);

	edge_t* iddle_state_aux = new edge_t[5];
	iddle_state = iddle_state_aux;
	edge_t iddle_state[6] =
	{
	{ Event_type::REVIVED, this->moving_state,  revive },
	{ Event_type::END_OF_TABLE, this->iddle_state, do_nothing }
	};

	copy_event(iddle_state_aux, iddle_state, 5);

}




GraphicCharacterFSM::~GraphicCharacterFSM()
{
}


