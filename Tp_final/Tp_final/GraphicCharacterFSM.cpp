#include "GraphicCharacterFSM.h"
#include "GraphicCharacterFSMRoutines.h"


GraphicCharacterFSM::GraphicCharacterFSM(Userdata* data) : FSM(data)
{
	moving_state = new std::vector<edge_t>();
	iddle_state = new std::vector<edge_t>();

	//moving_state
	moving_state->push_back({ Event_type::MOVE_TICKED, this->moving_state, move });
	moving_state->push_back({ Event_type::DIED, this->moving_state, die });
	moving_state->push_back({ Event_type::DISAPPEARED, this->iddle_state, disappear });
	moving_state->push_back({ Event_type::END_OF_TABLE, this->moving_state, do_nothing });

	//iddle_state
	iddle_state->push_back({ Event_type::REVIVED, this->moving_state,  revive });
	iddle_state->push_back({ Event_type::END_OF_TABLE, this->iddle_state, do_nothing });

}




GraphicCharacterFSM::~GraphicCharacterFSM()
{
	delete moving_state;
	delete iddle_state;
}


