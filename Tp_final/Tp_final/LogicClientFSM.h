#pragma once
#include "FSM_Class.h"

class LogicClientFSM: public FSM
{
public:
	LogicClientFSM(Userdata* data);
	~LogicClientFSM();

private:
	/****************************
		states
	******************************/
	std::vector<edge_t>* Initial_state;

	std::vector<edge_t>* Naming_me_state;
	std::vector<edge_t>* Naming_him_state;

	std::vector<edge_t>* Waiting_for_map_state;
	std::vector<edge_t>* Waiting_for_enemy_actions_state;
	std::vector<edge_t>* Waiting_for_servers_response_state;

	std::vector<edge_t>* Playing_state;

	std::vector<edge_t>* Waiting_for_ACK_quit_state;
	std::vector<edge_t>* Waiting_if_the_server_wants_to_play_again;
};

