#pragma once
#include "FSM_Class.h"
class GraphicCharacterFSM: public FSM
{
public:
	GraphicCharacterFSM(Userdata*data);
	~GraphicCharacterFSM();

	bool should_move = false;
	bool should_disappear = false;
	bool should_die = false;
	bool should_revive = false;

protected:
	/**********************
		states
	***********************/
	edge_t* moving_state = NULL;
	edge_t* iddle_state = NULL;
};

