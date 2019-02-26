#pragma once
#include "FSM_Class.h"

class PlayerActionsFSM : public FSM
{
public:
	PlayerActionsFSM(Userdata* data);
	~PlayerActionsFSM();

private:

	std::vector<edge_t>* walking_state = NULL;
	std::vector<edge_t>* jumping_state = NULL;
	std::vector<edge_t> * jumping_forward_state = NULL;
	std::vector<edge_t>* iddle_state = NULL;
	std::vector<edge_t>* attacking_state = NULL;
	std::vector<edge_t>* falling_state = NULL;
	std::vector<edge_t>* pushing_state = NULL;
	std::vector<edge_t>* dying_state = NULL;

};

