#pragma once
#include "LogicFSM.h"

class LogicClientFSM: public LogicFSM
{
public:
	LogicClientFSM(Userdata * data, LogicEventGenerator *event_gen, Scene* scene, Communication* com);
	~LogicClientFSM();
	void run_fsm(EventPackage * ev_pack);
	void reset_game();

protected:
	virtual void print_curr_state();
private:
	/****************************
		states
	******************************/
	std::vector<edge_t>* Initial_state;

	std::vector<edge_t>* Naming_me_state = NULL;
	std::vector<edge_t>* Naming_him_state = NULL;

	std::vector<edge_t>* Waiting_for_map_state = NULL;
	std::vector<edge_t>* Waiting_for_enemy_actions_state = NULL;

	std::vector<edge_t>* Playing_state = NULL;
	std::vector<edge_t>* Waiting_for_movement_state = NULL;

	std::vector<edge_t>* Waiting_for_ACK_quit_state = NULL;
	std::vector<edge_t>* Waiting_if_the_server_wants_to_play_again = NULL;
};

