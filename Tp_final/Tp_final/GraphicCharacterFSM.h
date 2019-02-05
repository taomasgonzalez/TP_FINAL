#pragma once
#include "FSM_Class.h"
class GraphicCharacterFSM: public FSM
{
public:
	GraphicCharacterFSM(Userdata*data);
	~GraphicCharacterFSM();

private:
	/**********************
		states
	***********************/
	edge_t* moving_state = NULL;
	edge_t* attacking_state = NULL;

};

