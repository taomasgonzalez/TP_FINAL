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

	edge_t * moving_state = NULL;
	edge_t * impacting_state = NULL;
};

