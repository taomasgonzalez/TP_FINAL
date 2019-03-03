#include "GraphicGameFSM.h"

void do_nothing_graphic(void * data);
void quit_graphic(void * data);
void draw(void * data);
void start_game_r(void* data);

GraphicGameFSM::GraphicGameFSM(DRAW * drawer) : FSM()
{
	this->drawer = drawer;

	iddle_state = new std::vector<edge_t>();
	menu_state = new std::vector<edge_t>();
	playing_state = new std::vector<edge_t>();

	//iddle_state
	//iddle_state->push_back({ Event_type::APPEARED, menu_state, start_menu});
	iddle_state->push_back({ Event_type::GAME_START, playing_state, start_game_r });
	iddle_state->push_back({ Event_type::END_OF_TABLE, iddle_state, do_nothing_graphic });

	//menu_state
	menu_state->push_back({ Event_type::LOCAL_QUIT, menu_state, quit_graphic });
	menu_state->push_back({ Event_type::EXTERN_QUIT, menu_state, quit_graphic });
	menu_state->push_back({Event_type::END_OF_TABLE, menu_state, do_nothing_graphic });

	//playing_state
	playing_state->push_back({Event_type::FPS_TICKED, playing_state, draw});
	//playing_state->push_back({Event_type::LOCAL_QUIT, menu_state, quit_graphic});
	//playing_state->push_back({Event_type::EXTERN_QUIT, menu_state, quit_graphic });
	playing_state->push_back({Event_type::LOCAL_QUIT, iddle_state, quit_graphic});
	playing_state->push_back({Event_type::EXTERN_QUIT, iddle_state, quit_graphic });
	playing_state->push_back({Event_type::END_OF_TABLE, playing_state, do_nothing_graphic });

	actual_state = iddle_state;
}


GraphicGameFSM::~GraphicGameFSM()
{
	delete iddle_state;
	delete menu_state;
	delete playing_state;
}
void GraphicGameFSM::start_game() {
	drawer->setLevel(0);
}

void GraphicGameFSM::draw_tick() {
	drawer->draw();
}

void do_nothing_graphic(void* data) {

}
void quit_graphic(void * data) {
	GraphicGameFSM* fsm =(GraphicGameFSM*) data;

}
void draw(void * data) {
	GraphicGameFSM* fsm = (GraphicGameFSM*)data;
	fsm->draw_tick();
}
void start_game_r(void* data) {
	GraphicGameFSM* fsm = (GraphicGameFSM*)data;
	fsm->start_game();
}


