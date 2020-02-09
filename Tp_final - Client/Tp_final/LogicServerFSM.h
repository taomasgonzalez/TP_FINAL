#pragma once
#include "LogicFSM.h"

class LogicServerFSM: public LogicFSM
{
public:
	LogicServerFSM(Userdata * data, LogicEventGenerator *event_gen, Scene* scene, Communication* com);
	~LogicServerFSM();

	void reset_game();

	bool control_enemies = false;
protected:
	void print_curr_state();
private:

	/****************************
	states
	******************************/

	virtual void run_fsm(EventPackage * ev_pack);

	std::vector<edge_t>* Initial_state = NULL;

	std::vector<edge_t>* Naming_him_state = NULL;
	std::vector<edge_t>* Naming_me_state = NULL;

	std::vector<edge_t>* Waiting_for_ACK_name_state = NULL;

	std::vector<edge_t>* Waiting_for_map_state = NULL;
	std::vector<edge_t>* Waiting_for_ACK_map_state = NULL;

	std::vector<edge_t>* Waiting_for_enemy_actions_state = NULL;
	std::vector<edge_t>* Waiting_for_ACK_enemy_actions_state = NULL;

	std::vector<edge_t>* Waiting_for_game_start_state = NULL;
	std::vector<edge_t>* Waiting_for_ACK_game_start_state = NULL;

	std::vector<edge_t>* Playing_state = NULL;

	std::vector<edge_t>* Waiting_for_ACK_quit_state = NULL;

	std::vector<edge_t>* Waiting_for_ACK_playing_state = NULL;

	std::vector<edge_t>* Waiting_if_the_client_wants_to_play_again = NULL;
	std::vector<edge_t>* Waiting_if_the_server_wants_to_play_again = NULL;
	std::vector<edge_t>* Waiting_if_the_user_wants_to_play_again = NULL;


	//debug!
	ALLEGRO_EVENT_QUEUE * control_ev_queue = NULL;
	ALLEGRO_TIMER* control_timer = NULL;
};

