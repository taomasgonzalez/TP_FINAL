#include "LogicServerFSM.h"
#include "LogicFSMRoutines.h"


LogicServerFSM::LogicServerFSM(Userdata * data) : FSM(data)
{
	edge_t *Initial_state_aux = new edge_t[5];
	this->Initial_state = Initial_state_aux;

	edge_t * Naming_him_state_aux = new edge_t[5];
	this->Naming_him_state = Naming_him_state_aux;

	edge_t* Naming_me_state_aux = new edge_t[5];
	this->Naming_me_state = Naming_me_state_aux;

	edge_t * Waiting_for_ACK_name_state_aux = new edge_t[5];
	this->Waiting_for_ACK_name_state = Waiting_for_ACK_name_state_aux;

	edge_t * Waiting_for_ACK_quit_state_aux = new edge_t[5];
	this->Waiting_for_ACK_quit_state = Waiting_for_ACK_quit_state_aux;

	edge_t* Waiting_for_ACK_map_state_aux = new edge_t[5];
	this->Waiting_for_ACK_map_state = Waiting_for_ACK_map_state_aux;

	edge_t* Waiting_for_ACK_enemy_actions_state_aux = new edge_t[6];
	this->Waiting_for_ACK_enemy_actions_state = Waiting_for_ACK_enemy_actions_state_aux;

	edge_t* Waiting_for_ACK_playing_state_aux = new edge_t[5];
	this->Waiting_for_ACK_playing_state = Waiting_for_ACK_playing_state_aux;

	edge_t* Waiting_for_ACK_game_start_state_aux = new edge_t[5];
	this->Waiting_for_ACK_game_start_state = Waiting_for_ACK_game_start_state_aux;

	edge_t * Playing_state_aux = new edge_t[11];
	this->Playing_state = Playing_state_aux;

	edge_t * Waiting_if_the_client_wants_to_play_again_aux = new edge_t[7];
	this->Waiting_if_the_client_wants_to_play_again = Waiting_if_the_client_wants_to_play_again_aux;

	edge_t * Waiting_if_the_user_wants_to_play_again_aux = new edge_t[7];
	this->Waiting_if_the_user_wants_to_play_again = Waiting_if_the_user_wants_to_play_again_aux;

	edge_t Initial_state[5] =
	{
		{ Event_type::START_COMMUNICATION, this->Naming_him_state, ask_for_name },
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Initial_state, do_nothing }
	};
	copy_event(Initial_state_aux, Initial_state, 5);

	edge_t Naming_him_state[5] =
	{
		{ Event_type::NAME_IS, this->Naming_me_state, receive_name_and_send_ack },
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Naming_him_state, do_nothing }
	};
	copy_event(Naming_him_state_aux, Naming_him_state, 5);

	edge_t Naming_me_state[5] =
	{
		{ Event_type::NAME, this->Waiting_for_ACK_name_state, send_name_is }, //
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Naming_me_state, do_nothing }
	};
	copy_event(Naming_me_state_aux, Naming_me_state, 5);

	edge_t  Waiting_for_ACK_name_state[5] =
	{
		{ Event_type::ACK, this->Waiting_for_ACK_map_state, send_map_is },
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit },					//se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Waiting_for_ACK_name_state, do_nothing }
	};
	copy_event(Waiting_for_ACK_name_state_aux, Waiting_for_ACK_name_state, 5);

	edge_t Waiting_for_ACK_map_state[5] =
	{

		{ Event_type::ACK, this->Waiting_for_ACK_enemy_actions_state,  traduciiondeloquescenealEVPaca((save_enemy_action) / ver caso ENEMYS_LOADED },

		{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
		{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
		{ Event_type::ERROR1, NULL, analayze_error },
		{ Event_type::END_OF_TABLE, this->Waiting_for_ACK_map_state, do_nothing }
	};
	copy_event(Waiting_for_ACK_map_state_aux, Waiting_for_ACK_map_state, 5);

	edge_t Waiting_for_ACK_enemy_actions_state[6] =
	{
		{ Event_type::ACK, this->Waiting_for_ACK_enemy_actions_state,  traduciiondeloquescenealEVPaca((save_enemy_action) },
		{ Event_type::ENEMY_ACTION, this->Waiting_for_ACK_enemy_actions_state,  send_enemy_action },
		{ Event_type::ENEMYS_LOADED, this->Waiting_for_ACK_game_start_state, send_game_start },
		{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
		{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
		{ Event_type::ERROR1, NULL, analayze_error },
		{ Event_type::END_OF_TABLE, this->Waiting_for_ACK_enemy_actions_state, do_nothing }
	};

	copy_event(Waiting_for_ACK_enemy_actions_state_aux, Waiting_for_ACK_enemy_actions_state, 6);

	edge_t Waiting_for_ACK_game_start_state[5] =
	{
		{ Event_type::ACK, this->Playing_state, execute_saved_enemy_actions }, //the game begins for the server
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Waiting_for_ACK_game_start_state, do_nothing }
	};

	copy_event(Waiting_for_ACK_game_start_state_aux, Waiting_for_ACK_game_start_state, 5);

	edge_t Playing_state[11] =
	{
	{ Event_type::ENEMY_ACTION, this->Waiting_for_ACK_playing_state, execute_and_send_enemy_action }, //local ENEMY_ACTION evento software already loaded, only has to be sent
	{ Event_type::MOVE, this->Waiting_for_ACK_playing_state, execute_action_send_it_and_set_ack_time_out }, //MOVE local generado desde allegro, has to be send to the client if valid
	{ Event_type::ATTACK, this->Waiting_for_ACK_playing_state, execute_action_send_it_and_set_ack_time_out }, //ATTACK local generado desde allegro, has to be send to the client if valir
	{ Event_type::ACTION_REQUEST, this->Waiting_for_ACK_playing_state, load_action_and_send_it_back },   //AR del cliente
	{ Event_type::FINISHED_LEVEL, this->Waiting_for_ACK_map_state, send_map_is },		//evento de software que se termino el nivel
	{ Event_type::WE_WON, this->Waiting_if_the_client_wants_to_play_again, send_we_won }, //we_won local generado por soft, le aviso a client que ganamos
	{ Event_type::GAME_OVER, this->Waiting_if_the_client_wants_to_play_again, send_we_lost },  //game_over local generado por soft, le aviso a client que perdimos
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Playing_state_aux, Playing_state, 11);

	edge_t Waiting_for_ACK_playing_state[5] =
	{
		{ Event_type::ACK, this->Playing_state, received_ack_routine }, //Se recibe un ACK del clinte de un MOVE/ATTACK enviado
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Waiting_for_ACK_playing_state_aux, Waiting_for_ACK_playing_state, 5);


	edge_t Waiting_if_the_client_wants_to_play_again[7] =
	{
		{ Event_type::PLAY_AGAIN, this->Waiting_if_the_user_wants_to_play_again, ask_user_being_server_and_send_decition }, //se recibe un PLAY_AGAIN del client que quiere volver a jugar
	{ Event_type::GAME_OVER, NULL, tell_user_send_ack_and_finish_game },  //se recibe un GAME_OVER del client que no quiere volver a jugar
	{ Event_type::ACK, NULL, finish_game },								//validación del client a un paquete GAME_OVER mandado por el servidor desde ask_user_and_send_decition()
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Waiting_if_the_client_wants_to_play_again_aux, Waiting_if_the_client_wants_to_play_again, 7);

	edge_t Waiting_if_the_user_wants_to_play_again[7] =
	{
		{ Event_type::PLAY_AGAIN, this->Waiting_for_ACK_map_state, send_map_is },  //el usuario del servidor quiere volver a jugar
	{ Event_type::GAME_OVER, this->Waiting_if_the_user_wants_to_play_again, send_game_over }, //el usuario del servidor no quiere volver a jugar
	{ Event_type::ACK, NULL, finish_game },										//ACK del GAME_OVER del usuario del servidor
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Waiting_if_the_user_wants_to_play_again_aux, Waiting_if_the_user_wants_to_play_again, 7);


	edge_t Waiting_for_ACK_quit_state[5] =
	{
		{ Event_type::ACK, NULL, finish_game },
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Waiting_for_ACK_quit_state, do_nothing }
	};

	copy_event(Waiting_for_ACK_quit_state_aux, Waiting_for_ACK_quit_state, 5);

	this->actual_state = this->Initial_state;

}


LogicServerFSM::~LogicServerFSM()
{
	delete Initial_state;

	delete Naming_him_state;
	delete Naming_me_state;

	delete Waiting_for_ACK_name_state;

	delete Waiting_for_map_state;
	delete Waiting_for_ACK_map_state;

	delete Waiting_for_enemy_actions_state;
	delete Waiting_for_ACK_enemy_actions_state;

	delete Waiting_for_game_start_state;
	delete Waiting_for_ACK_game_start_state;

	delete Playing_state;

	delete Waiting_for_ACK_quit_state;

	delete Waiting_for_ACK_playing_state;
	delete Waiting_for_servers_response_state;

	delete Waiting_if_the_client_wants_to_play_again;
	delete Waiting_if_the_server_wants_to_play_again;
	delete Waiting_if_the_user_wants_to_play_again;
}

