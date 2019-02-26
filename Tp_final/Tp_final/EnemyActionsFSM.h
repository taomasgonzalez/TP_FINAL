#pragma once
#include "FSM_Class.h"
class EnemyActionsFSM: public FSM
{
public:
	EnemyActionsFSM(Userdata* data);
	~EnemyActionsFSM();
private:

	std::vector<edge_t>* walking_state = NULL;
	std::vector<edge_t>* jumping_state = NULL;
	std::vector<edge_t>* jumping_forward_state = NULL;
	std::vector<edge_t>* iddle_state = NULL;
	std::vector<edge_t>* trapped_state = NULL;

	std::vector<edge_t>* attacking_state = NULL;
	std::vector<edge_t>* falling_state = NULL;
	std::vector<edge_t>* dying_state = NULL;

};

