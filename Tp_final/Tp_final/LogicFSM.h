#pragma once
#include "FSM_Class.h"


/*******************************************************************************
CLASE TIME_OUT
******************************************************************************/
enum class time_out_type {
	Time_out_move,
	Time_out_quit,
	Time_out_i_am_ready

};

class LogicFSM : public FSM
{
public:
	LogicFSM(Userdata * data);
	~LogicFSM();

	/*****************************
		observer related	
	******************************/
	//sending
	bool s_quit = false;
	bool s_ack = false;
	bool s_name_is = false;
	bool s_error = false;
	bool s_map_is = false;
	bool s_game_start = false;
	bool s_enemy_action = false;
	bool s_action_request = false;
	bool s_action_from_action_request = false;
	bool s_action = false;
	bool s_game_over = false;
	bool s_we_won = false;
	bool s_play_again = false;
	bool s_name = false;

	//user decition flags
	bool want_to_play_again = false;


	//game conditions flags
	bool we_won = false;
	bool we_lost = false;

	bool waiting_for_ack = false;
	bool reset_ack_timer = false;
	bool new_ack_time_out = false;
	bool end_game = false;
	bool receive_name = false;

	//execute falgs
	bool ex_action = false;
	bool ex_saved_enemy_actions = false;

	bool start_game = false;

	//check flags
	bool check_action = false;
	bool check_map = false;
	bool valid_local_action = false;
	bool valid_extern_action = false;
	bool error_ocurred = false;

	//loading
	bool ld_enemy_action = false; //for client
	bool sv_enemy_action = false; //for server
	bool ld_new_map = false;
	bool ld_play_again = false;
	bool ld_game_over = false;


private:
	/****************************
		states
	******************************/


	edge_t* Initial_state = NULL;

	edge_t* Naming_him_state = NULL;
	edge_t* Naming_me_state = NULL;

	edge_t* Waiting_for_ACK_name_state = NULL;

	edge_t* Waiting_for_map_state = NULL;
	edge_t* Waiting_for_ACK_map_state = NULL;

	edge_t* Waiting_for_enemy_actions_state = NULL;
	edge_t* Waiting_for_ACK_enemy_actions_state = NULL;

	edge_t* Waiting_for_game_start_state = NULL;
	edge_t* Waiting_for_ACK_game_start_state = NULL;

	edge_t* Playing_state = NULL;

	edge_t* Waiting_for_ACK_quit_state = NULL;

	edge_t* Waiting_for_ACK_playing_state = NULL;
	edge_t* Waiting_for_servers_response_state = NULL;

	edge_t* Waiting_if_the_client_wants_to_play_again = NULL;
	edge_t* Waiting_if_the_server_wants_to_play_again = NULL;
	edge_t* Waiting_if_the_user_wants_to_play_again = NULL;

	/*********************************
		initializers
	**********************************/
	void init_fsm_server();
	void init_fsm_client();
};

