#pragma once
#include "GraphicCharacterFSM.h"
class GraphicAttackCharacterFSM : public GraphicCharacterFSM
{
public:
	GraphicAttackCharacterFSM(Userdata*data);
	~GraphicAttackCharacterFSM();

	bool should_attack = false;
	bool should_finish_attack = false;

protected:
	/**********************
			states
	***********************/
	edge_t* attacking_state = NULL;

};

