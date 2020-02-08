#include "GraphicGameFSM.h"

void do_nothing_graphic(void * data);
void quit_graphic(void * data);
void draw(void * data);
void start_game_r(void* data);
void change_level_r(void* data);

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
	playing_state->push_back({ Event_type::CHANGE_LEVEL, playing_state, change_level_r });

	playing_state->push_back({Event_type::LOCAL_QUIT, iddle_state, quit_graphic});
	playing_state->push_back({Event_type::EXTERN_QUIT, iddle_state, quit_graphic });
	playing_state->push_back({Event_type::END_OF_TABLE, playing_state, do_nothing_graphic });

	actual_state = iddle_state;
	this->level = 1;
}



GraphicGameFSM::~GraphicGameFSM()
{
	delete iddle_state;
	delete menu_state;
	delete playing_state;
}
void GraphicGameFSM::start_game() {
	//should start the graphic timer for fps events!!
	drawer->setLevel(level);
	drawer->play_main_song();
	Userdata::generating_graphic_events = true;

	//drawer->draw();
}

void GraphicGameFSM::draw_tick() {
	drawer->draw();
}

void GraphicGameFSM::change_level() {

	level++;
	drawer->setLevel(level);

}


void do_nothing_graphic(void* data) {

}
void quit_graphic(void * data) {
	GraphicGameFSM* fsm =(GraphicGameFSM*) data;
	//Userdata::generating_graphic_events = false;
}
void draw(void * data) {
	GraphicGameFSM* fsm = (GraphicGameFSM*)data;
	fsm->draw_tick();
}
void start_game_r(void* data) {
	GraphicGameFSM* fsm = (GraphicGameFSM*)data;
	fsm->start_game();
}


void change_level_r(void* data)
{
	GraphicGameFSM* fsm = (GraphicGameFSM*)data;
	fsm->change_level();
}