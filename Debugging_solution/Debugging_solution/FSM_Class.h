#pragma once
/*******************************************************************************
					INCLUDED HEADERS
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Observable.h"
#include "EventPackage.h"

/*****************************************************
*          DEFINITION OF EDGE
* **************************************************/
typedef struct edge edge_t;
struct edge
{
		Event_type event;
		edge_t* nextstate;
		void(*fun_trans)(void*);


};


/*******************************************************************************
							CLASE TIME_OUT
******************************************************************************/
enum class time_out_type {
	Time_out_move,
	Time_out_quit,
	Time_out_i_am_ready

};

/*******************************************************************************
							CLASE FSM
******************************************************************************/
class FSM : public  Observable{
public:
	 FSM(Userdata * data);
	 void run_fsm(EventPackage * ev_pack);
	 void init_fsm();
		
	 EventPackage* get_fsm_ev_pack();
	 void load_fsm_ev_pack(EventPackage* event_package_to_be_loaded);
	 edge_t * give_me_the_actual_state();

	 //sending
	 bool s_quit;
	 bool s_ack;
	 bool s_name_is;
	 bool s_error;
	 bool s_map_is;
	 bool s_game_start;
	 bool s_enemy_action;
	 bool s_action_request;
	 bool s_action_from_action_request;
	 bool s_action;
	 bool s_game_over;
	 bool s_we_won;
	 bool s_play_again;
	 bool s_name;

	 //user decition flags
	 bool want_to_play_again;


	 //game conditions flags
	 bool we_won;
	 bool we_lost;

	 bool waiting_for_ack;
	 bool reset_ack_timer;
	 bool new_ack_time_out;
	 bool end_game;
	 bool receive_name;

	//execute falgs
	 bool ex_action;
	 bool ex_saved_enemy_actions;

	 bool start_game;

	 //check flags
	 bool check_action;
	 bool check_map;
	 bool valid_local_action;
	 bool valid_extern_action;
	 bool error_ocurred;

	 //loading
	 bool ld_enemy_action; //for client
	 bool sv_enemy_action; //for server
	 bool ld_new_map;
	 bool ld_play_again;
	 bool ld_game_over;

private:


	edge_t * actual_state = NULL;

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

	
	EventPackage* my_ev_pack;
	
	void check_for_incorrect_event(Event_type event);
	Userdata * my_user_data;
	
	void init_fsm_server();
	void init_fsm_client();
};


/*******************************************************************************
			CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/

/*******************************************************************************
						ENUMS, STRUCTS Y TYPEDEFS
******************************************************************************/

typedef enum { OFF, ON } switch_t;

typedef unsigned int uint;

