#pragma once
#include "FSM_Class.h"
#include "DRAW.h"

class GraphicGameFSM : public FSM
{
public:
	GraphicGameFSM(DRAW * drawer);
	~GraphicGameFSM();

	void start_game();
	void draw_tick();
	void change_level();

private:
	std::vector<edge_t>* iddle_state = NULL;
	std::vector<edge_t>* menu_state = NULL;
	std::vector<edge_t>* playing_state = NULL;

	unsigned int level;
	DRAW* drawer = NULL;
};

