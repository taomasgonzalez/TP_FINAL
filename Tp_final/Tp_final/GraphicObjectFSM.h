#pragma once
#include "FSM_Class.h"
#include "DRAW.h"

class GraphicObjectFSM: public FSM
{
public:
	GraphicObjectFSM(Userdata* data, DRAW* drawer, unsigned int id);
	~GraphicObjectFSM();

protected:
	std::vector<edge_t>* drawing_state;
	std::vector<edge_t>* waiting_to_draw_state;
	std::vector<edge_t> * inactive_state;

	DRAW* drawer;
	unsigned int id;
};

