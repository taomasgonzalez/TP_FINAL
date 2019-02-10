#pragma once
#include "FSM_Class.h"
#include "DRAW.h"

class GraphicGameFSM : public FSM
{
public:
	GraphicGameFSM(Userdata * data, DRAW * drawer);
	~GraphicGameFSM();

private:
	std::vector<edge_t>* menu_state = NULL;
	std::vector<edge_t>* playing_state = NULL;

	DRAW* drawer;
};

