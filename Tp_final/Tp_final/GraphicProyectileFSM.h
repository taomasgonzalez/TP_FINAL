#pragma once
#include "FSM_Class.h"
class GraphicProyectileFSM: public FSM
{
public:
	GraphicProyectileFSM(Userdata* data);
	~GraphicProyectileFSM();

	bool should_move = false;
	bool should_impact = false;
	bool should_disappear = false;

private:
	/**********************
		states
	***********************/

	std::vector<edge_t>* moving_state = NULL;
	std::vector<edge_t>* impacting_state = NULL;
};

