#pragma once
#include "FSM_Class.h"
class GraphicCharacterFSM: public FSM
{
public:
	GraphicCharacterFSM(Userdata*data);
	~GraphicCharacterFSM();

	bool should_move = false;
	bool should_attack = false;
	bool should_disappear = false;

private:
	/**********************
		states
	***********************/
	edge_t* moving_state = NULL;
	edge_t* attacking_state = NULL;

};

