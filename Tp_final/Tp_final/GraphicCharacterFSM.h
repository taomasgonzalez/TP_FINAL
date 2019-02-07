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
	std::vector<edge_t>* moving_state = NULL;
	std::vector<edge_t>* iddle_state = NULL;
};

