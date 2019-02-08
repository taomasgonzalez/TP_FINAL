#include "GraphicGameFSM.h"

void do_nothing(void* data);

GraphicGameFSM::GraphicGameFSM(Userdata * data, DRAW * drawer): FSM(data)
{
	this->drawer = drawer;

	closed_state = new std::vector<edge_t>();
	menu_state = new std::vector<edge_t>();
	playing_state = new std::vector<edge_t>();

	//closed_state
	//closed_state->push_back({Event_type::,this->menu_state, start_menu});
	//closed_state->push_back({ Event_type::END_OF_TABLE, this->closed_state, do_nothing });

	//menu_state
	//menu_state->push_back({Event_type::, });

	//drawing_state
	actual_state = closed_state;
}


GraphicGameFSM::~GraphicGameFSM()
{
	delete menu_state;
	delete closed_state;
	delete playing_state;
}

void do_nothing(void* data) {

}