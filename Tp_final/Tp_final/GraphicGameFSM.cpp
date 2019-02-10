#include "GraphicGameFSM.h"

void do_nothing_graphic(void * data);
void quit_graphic(void * data);
void draw(void * data);

GraphicGameFSM::GraphicGameFSM(Userdata * data, DRAW * drawer) : FSM(data)
{
	this->drawer = drawer;

	menu_state = new std::vector<edge_t>();
	playing_state = new std::vector<edge_t>();


	//menu_state
	menu_state->push_back({ Event_type::LOCAL_QUIT,this->menu_state, quit_graphic });
	playing_state->push_back({ Event_type::EXTERN_QUIT, this->menu_state, quit_graphic });
	menu_state->push_back({Event_type::END_OF_TABLE, this->menu_state, do_nothing_graphic });

	//playing_state
	playing_state->push_back({Event_type::FPS_TICKED, this->playing_state, draw});
	playing_state->push_back({Event_type::LOCAL_QUIT, this->menu_state, quit_graphic});
	playing_state->push_back({Event_type::EXTERN_QUIT, this->menu_state, quit_graphic });
	playing_state->push_back({Event_type::END_OF_TABLE, this->playing_state, do_nothing_graphic });

	actual_state = menu_state;
}


GraphicGameFSM::~GraphicGameFSM()
{
	delete menu_state;
	delete playing_state;
}

void do_nothing_graphic(void* data) {

}
void quit_graphic(void * data) {

}
void draw(void * data) {

}
