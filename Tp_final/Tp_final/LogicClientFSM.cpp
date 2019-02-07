#include "LogicClientFSM.h"
#include "LogicFSMRoutines.h"

LogicClientFSM::LogicClientFSM(Userdata* data): FSM(data){

	edge_t * Initial_state_aux = new edge_t[5];
	this->Initial_state = Initial_state_aux;

	edge_t* Naming_me_state_aux = new edge_t[5];
	this->Naming_me_state = Naming_me_state_aux;

	edge_t * Naming_him_state_aux = new edge_t[5];
	this->Naming_him_state = Naming_him_state_aux;

	edge_t* Waiting_for_map_state_aux = new edge_t[5];
	this->Waiting_for_map_state = Waiting_for_map_state_aux;

	edge_t* Waiting_for_enemy_actions_state_aux = new edge_t[6];
	this->Waiting_for_enemy_actions_state = Waiting_for_enemy_actions_state_aux;

	edge_t * Waiting_for_servers_response_state_aux = new edge_t[5];
	this->Waiting_for_servers_response_state = Waiting_for_servers_response_state_aux;

	edge_t * Playing_state_aux = new edge_t[9];
	this->Playing_state = Playing_state_aux;

	edge_t * Waiting_for_ACK_quit_state_aux = new edge_t[5];
	this->Waiting_for_ACK_quit_state = Waiting_for_ACK_quit_state_aux;

	edge_t * Waiting_if_the_server_wants_to_play_again_aux = new edge_t[7];
	this->Waiting_if_the_server_wants_to_play_again = Waiting_if_the_server_wants_to_play_again_aux;


	edge_t Initial_state[5] =
	{
		{ Event_type::NAME, this->Naming_me_state,  send_name_is },
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Initial_state, do_nothing }
	};
	copy_event(Initial_state_aux, Initial_state, 5);


	edge_t Naming_me_state[5] =
	{
		{ Event_type::ACK, this->Naming_him_state, ask_for_name }, //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Naming_me_state, do_nothing }
	};
	copy_event(Naming_me_state_aux, Naming_me_state, 5);

	edge_t Naming_him_state[5] =
	{
		{ Event_type::NAME_IS, this->Waiting_for_map_state, receive_name_and_send_ack }, //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Naming_him_state, do_nothing }
	};
	copy_event(Naming_him_state_aux, Naming_him_state, 5);

	edge_t  Waiting_for_map_state[5] =
	{
		{ Event_type::MAP_IS, this->Waiting_for_enemy_actions_state, check_map_and_save_send_ack },
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Waiting_for_map_state, do_nothing }
	};
	copy_event(Waiting_for_map_state_aux, Waiting_for_map_state, 5);


	edge_t Waiting_for_enemy_actions_state[6] =
	{
		{ Event_type::ENEMY_ACTION, this->Waiting_for_enemy_actions_state, load_enemy_action_and_send_ack },
	{ Event_type::GAME_START, this->Playing_state, start_game_and_send_ack }, //the game begins for the client
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Waiting_for_enemy_actions_state, do_nothing }
	};

	copy_event(Waiting_for_enemy_actions_state_aux, Waiting_for_enemy_actions_state, 6);


	edge_t Playing_state[9] =
	{
		{ Event_type::ENEMY_ACTION, this->Playing_state, execute_receive_action_and_send_ack },
	{ Event_type::ACTION_REQUEST, this->Waiting_for_servers_response_state, check_and_send_action_request },  //Action request generate by allegro, has to be send to the server
	{ Event_type::MAP_IS, this->Waiting_for_ACK_map_state, check_map_and_save_send_ack }, //next level
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::WE_WON, this->Waiting_if_the_server_wants_to_play_again, analyze_we_won }, // WE_WON from the server, must be analyzed
	{ Event_type::GAME_OVER, this->Waiting_if_the_server_wants_to_play_again, analyze_we_lost },// GAME_OVER from the server, must be analyzed
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Playing_state_aux, Playing_state, 9);


	edge_t Waiting_for_servers_response_state[6] =
	{
		{ Event_type::MOVE, this->Playing_state, execute_receive_action_and_send_ack },  //extern MOVE that arrives through networking , has to be checked
	{ Event_type::ATTACK, this->Playing_state, execute_receive_action_and_send_ack },  //extern ATTACK that arrives through networking , has to be checked
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Waiting_for_servers_response_state_aux, Waiting_for_servers_response_state, 6);

	edge_t Waiting_if_the_server_wants_to_play_again[7] =
	{
		{ Event_type::ACK, NULL, finish_game },  //ack of my game over from the server
	{ Event_type::MAP_IS, this->Waiting_for_enemy_actions_state, check_map_and_save_send_ack }, ////Client wants to play again, server too
	{ Event_type::GAME_OVER, NULL, tell_user_send_ack_and_finish_game },  //Client wants to play again, server doesn´t 
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Waiting_if_the_server_wants_to_play_again, do_nothing }
	};

	copy_event(Waiting_if_the_server_wants_to_play_again_aux, Waiting_if_the_server_wants_to_play_again, 7);

	edge_t Waiting_for_ACK_quit_state[5] =
	{
		{ Event_type::ACK, NULL, finish_game },
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::END_OF_TABLE, this->Waiting_for_ACK_quit_state, do_nothing }
	};

	copy_event(Waiting_for_ACK_quit_state_aux, Waiting_for_ACK_quit_state, 5);

	this->actual_state = this->Initial_state;

}


LogicClientFSM::~LogicClientFSM()
{
	delete Initial_state;

	delete Naming_me_state;
	delete Naming_him_state;

	delete Waiting_for_map_state;
	delete Waiting_for_enemy_actions_state;
	delete Waiting_for_servers_response_state;

	delete Playing_state;

	delete Waiting_for_ACK_quit_state;
	delete Waiting_if_the_server_wants_to_play_again;
}

