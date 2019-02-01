/*******************************************************************************
                      INCLUDED HEADERS a
******************************************************************************/
#include "FSM_Class.h"


void do_nothing(void * data);//Dummy for the debugging of the protocol structure

//analyze
void analyze_action_being_client(void* data);
void analayze_quit(void*data);
void analayze_error(void*data);
void analyze_we_won(void*data); //to do
void analyze_we_lost(void*data); //to do
void check_action_request(void* data);

//send
void send_map_is(void * data);
void send_ack(void * data);
void send_quit(void * data);
void send_name_is(void* data);
void send_ack_and_quit(void* data);
void execute_and_send_enemy_action(void* data);
void send_game_start(void* data);
void send_error_and_finish_game(void* data);
void send_action_and_set_ack_time_out(void* data);
void send_next_map(void*data);  //to do
void send_we_won(void*data); 
void send_we_lost(void*data);
void send_game_over(void*data); 
void send_play_again(void*data); 
void send_enemy_action(void*data);
void save_enemy_action_and_send_it(void* data);
void send_action_request_and_set_ack_time_out(void* data); //for client

//UI
void tell_user_send_ack_and_finish_game(void*data); //to do
void ask_the_user_if_wants_to_play_again(void*data); //to do
void ask_user_being_client_and_send_decition(void*data); //to do
void ask_user_being_server_and_send_decition(void*data);

//execute
void execute_receive_action_and_send_ack(void*data); //for client
void execute_action_send_it_and_set_ack_time_out(void* data); //for server
void execute_receive_action_request_send_action_and_send_ack(void * data); //for server
void execute_saved_enemy_actions(void* data);




//mapping
void check_map_and_save_send_ack(void* data);
void check_sum_and_send_ack(void* data);

//timers
void set_ack_time_out(void* data);
void received_ack_routine(void* data);

//others
void ask_for_name(void* data);
void finish_game(void * data);
void start_game_and_send_ack(void* data);
void receive_name_and_send_ack(void*data);
void check_and_send_action_request(void*data);

//loading
void load_and_send_enemy_action(void*data); //to do
void load_enemy_action_and_send_ack(void* data);
void load_action_and_send_it_back(void* data);
void load_enemy_action(void* data);
void save_enemy_action(void* data);



void copy_event(edge_t* to_copy, edge_t* to_be_copied, int length);


/*******************************************************************************
							FSM CONSTRCUTOR
******************************************************************************/

FSM::FSM(Userdata * data) : Observable(Observable_type::FSM){

	this->my_user_data = data;

	if (data->my_network_data.is_client())
		init_fsm_client();
	else 
		init_fsm_server();

	//sending flags
	s_quit = false;
	s_ack = false;
	s_name_is = false;
	s_error = false;
	s_map_is = false;
	s_game_start = false;
	s_enemy_action = false;
	s_action_request = false;
	s_action = false;
	s_action_from_action_request = false;
	s_name = false;

	//timer flags
	waiting_for_ack = false;
	reset_ack_timer = false;
	new_ack_time_out = false;

	//user decition flags
	want_to_play_again = false;



	//others flags
	end_game = false;
	start_game = false;
	receive_name = false;
	ex_action = false;
	ex_saved_enemy_actions=false;


	//check flags
	check_action = false;
	check_map = false;
	check_local_action_request = false;
	valid_local_action_request = false;
	error_ocurred = false;


	//loading flags
	ld_enemy_action = false;
	ld_new_map=false;
	sv_enemy_action = false;
	ld_play_again = false;
	ld_game_over = false;


	//game conditions flags
	bool we_won=false;
	bool we_lost=false;


}


/*******************************************************************************
                           FSM_SERVER CONSTRCUTOR
******************************************************************************/

void FSM::init_fsm_server(){

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

	edge_t* Waiting_for_ACK_map_state_aux = new edge_t [5];
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
	{ Event_type::ACK, this->Waiting_for_ACK_enemy_actions_state,  save_enemy_action_and_send_it },
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Waiting_for_ACK_map_state, do_nothing }
	};
	copy_event(Waiting_for_ACK_map_state_aux, Waiting_for_ACK_map_state, 5);

	edge_t Waiting_for_ACK_enemy_actions_state[6] =
	{
	{ Event_type::ACK, this->Waiting_for_ACK_enemy_actions_state, save_enemy_action_and_send_it },
	{ Event_type::ENEMYS_LOADED, this->Waiting_for_ACK_game_start_state, send_game_start},
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
	{ Event_type::ENEMY_ACTION, this->Waiting_for_ACK_playing_state, execute_and_send_enemy_action}, //local ENEMY_ACTION evento software already loaded, only has to be sent
	{ Event_type::MOVE, this->Waiting_for_ACK_playing_state, execute_action_send_it_and_set_ack_time_out}, //MOVE local generado desde allegro, has to be send to the client if valid
	{ Event_type::ATTACK, this->Waiting_for_ACK_playing_state, execute_action_send_it_and_set_ack_time_out}, //ATTACK local generado desde allegro, has to be send to the client if valir
	{ Event_type::ACTION_REQUEST, this->Waiting_for_ACK_playing_state, load_action_and_send_it_back},   //AR del cliente
	{ Event_type::FINISHED_LEVEL, this->Waiting_for_ACK_map_state, send_map_is},		//evento de software que se termino el nivel
	{ Event_type::WE_WON, this->Waiting_if_the_client_wants_to_play_again, send_we_won}, //we_won local generado por soft, le aviso a client que ganamos
	{ Event_type::GAME_OVER, this->Waiting_if_the_client_wants_to_play_again, send_we_lost},  //game_over local generado por soft, le aviso a client que perdimos
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Playing_state_aux, Playing_state, 11);

	edge_t Waiting_for_ACK_playing_state[5]=
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
	{ Event_type::PLAY_AGAIN, this->Waiting_if_the_user_wants_to_play_again, ask_user_being_server_and_send_decition}, //se recibe un PLAY_AGAIN del client que quiere volver a jugar
	{ Event_type::GAME_OVER, NULL, tell_user_send_ack_and_finish_game},  //se recibe un GAME_OVER del client que no quiere volver a jugar
	{ Event_type::ACK, NULL, finish_game },								//validación del client a un paquete GAME_OVER mandado por el servidor desde ask_user_and_send_decition()
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Waiting_if_the_client_wants_to_play_again_aux, Waiting_if_the_client_wants_to_play_again, 7);

	edge_t Waiting_if_the_user_wants_to_play_again[7] =
	{
	{ Event_type::PLAY_AGAIN, this->Waiting_for_ACK_map_state, send_map_is},  //el usuario del servidor quiere volver a jugar
	{ Event_type::GAME_OVER, this->Waiting_if_the_user_wants_to_play_again, send_game_over}, //el usuario del servidor no quiere volver a jugar
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


/*******************************************************************************
FSM_CLIENT CONSTRCUTOR
******************************************************************************/
void FSM::init_fsm_client() {

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
	{ Event_type::NAME, this->Naming_me_state,  send_name_is},
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
	{ Event_type::ENEMY_ACTION, this->Playing_state, execute_receive_action_and_send_ack},
	{ Event_type::ACTION_REQUEST, this->Waiting_for_servers_response_state, check_and_send_action_request},  //Action request generate by allegro, has to be send to the server
	{ Event_type::MAP_IS, this->Waiting_for_ACK_map_state, check_map_and_save_send_ack }, //next level
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::WE_WON, this->Waiting_if_the_server_wants_to_play_again, analyze_we_won}, // WE_WON from the server, must be analyzed
	{ Event_type::GAME_OVER, this->Waiting_if_the_server_wants_to_play_again, analyze_we_lost},// GAME_OVER from the server, must be analyzed
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Playing_state_aux, Playing_state, 9);
	

	edge_t Waiting_for_servers_response_state[6] =
	{
	{ Event_type::MOVE, this->Playing_state, execute_receive_action_and_send_ack},  //extern MOVE that arrives through networking , has to be checked
	{ Event_type::ATTACK, this->Playing_state, execute_receive_action_and_send_ack},  //extern ATTACK that arrives through networking , has to be checked
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Waiting_for_servers_response_state_aux, Waiting_for_servers_response_state, 6);
	
	edge_t Waiting_if_the_server_wants_to_play_again[7] =
	{
	{ Event_type::ACK, NULL, finish_game },  //ack of my game over from the server
	{ Event_type::MAP_IS, this->Waiting_for_enemy_actions_state, check_map_and_save_send_ack}, ////Client wants to play again, server too
	{ Event_type::GAME_OVER, NULL, tell_user_send_ack_and_finish_game},  //Client wants to play again, server doesn´t 
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


/******************************************************************************
*******************************************************************************
					PRIVATE METHODS DEFINITIONS
*******************************************************************************

/**************************************************************
					run_fsm
**************************************************************/
/*
*This function runs the FSM with a given input.
*
*INPUT:
*The event that is hold in the edge that contains the action routine.
*
*OUTPUT:
*Void
*/
void FSM:: run_fsm(EventPackage * ev_pack)
{
	Event_type event1 = ev_pack->give_me_your_event_type();
	this->my_ev_pack = ev_pack;

	while ((this->actual_state->event != event1) && (this->actual_state->event != Event_type::END_OF_TABLE))
	{	
		this->actual_state++;
	}

	//genera evento de software en caso de haber encontrado un evento que no debería ocurrir en ese estado.s MANDAR ERROR, NO PUEDE LLEGAR UN MOVE AL PRINICIPIO XEJ
	//if (this->actual_state->event == My_Event::END_OF_TABLE) 
	//	this->check_for_incorrect_event(event1);			

	//Runs the functions related to that event
	(this->actual_state->fun_trans)(this);
	this->actual_state = (this->actual_state->nextstate);


}

void FSM::check_for_incorrect_event(Event_type event) {
	//if(this->actual_state == this->Waiting..) {

	//}
}

void FSM::init_fsm()
{
	/*aca irian las inicializaciones comunes a tanto server como client. 
	Habria que chequear que para ese estado en particular, todos los estados a los cuales transicionar
	sean iguales para modo server y modo cliente, y tambien todos los eventos 
	Y LAS RUTINAS DE ACCION!!!
	*/
}
 
 void do_nothing(void* data)
{

}

void send_name_is(void* data ) {
	FSM * fsm = (FSM*)data;
	fsm->s_name_is = true;
	fsm->notify_obs();
	fsm->s_name_is = false;
	set_ack_time_out(data);
 }

 
void analayze_quit(void*data)
{
	FSM * fsm = (FSM*)data;
	if (fsm->get_fsm_ev_pack()->is_this_a_local_action())
		send_quit(data);
	else
		send_ack_and_quit(data);
}

//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
 void send_quit(void* data) {
	 FSM * fsm = (FSM*)data;
	 fsm->s_quit = true;
	 fsm->notify_obs();
	 fsm->s_quit = false; 
	 set_ack_time_out(data);

}

 //se devuelve un ACK con ID 0 para la otra compu, se sale
 void send_ack_and_quit(void* data) {

	 //Interfaz del usuario avisando la situación
	 send_ack(data);
	 finish_game(data);
}

 void analayze_error(void*data)
 {
	 FSM * fsm = (FSM*)data;
	 if (fsm->get_fsm_ev_pack()->is_this_a_local_action())
		 send_error_and_finish_game(data);
	 else
		 finish_game(data);
 }

 //Se sale del programa sin avisar, rutina de acción del evento ERROR1
void finish_game(void * data) {

	FSM * fsm = (FSM*)data;
	fsm->end_game = true;
	fsm->notify_obs();
	//si bien esto es innecesario a simple vista, lo pongo en false por las dudas que tenga que volver a iniciar el juego desde menu
	fsm->end_game = false;
}

void received_ack_routine(void* data) {
	FSM * fsm = (FSM*)data;
	fsm->reset_ack_timer = true;
	fsm->notify_obs();
	fsm->reset_ack_timer = false;
}

void check_sum_and_send_ack(void* data) {

}

void send_error_and_finish_game(void* data) {
	FSM * fsm = (FSM*)data;
	fsm->s_error = true;
	fsm->notify_obs();
	fsm->s_error = false;
}

void execute_and_send_enemy_action(void* data) {
	FSM * fsm = (FSM*)data;

	fsm->ex_action = true;
	fsm->notify_obs();
	fsm->ex_action = false;
	send_enemy_action(data);
	set_ack_time_out(data);
}

void save_enemy_action_and_send_it(void* data) {

	save_enemy_action(data);
	send_enemy_action(data);
}
void execute_saved_enemy_actions(void* data) {
	FSM * fsm = (FSM*)data;

	fsm->ex_saved_enemy_actions = true;
	fsm->notify_obs();
	fsm->ex_saved_enemy_actions = false;
}



void save_enemy_action(void* data) {

	FSM * fsm = (FSM*)data;

	fsm->sv_enemy_action = true;
	fsm->notify_obs();
	fsm->sv_enemy_action = false;
}
void send_enemy_action(void* data) {
	
	FSM * fsm = (FSM*)data;

	fsm->s_enemy_action = true;
	fsm->notify_obs();
	fsm->s_enemy_action = false;
}

void send_game_start(void* data) {
	FSM * fsm = (FSM*)data;
	fsm->s_game_start = true;
	fsm->notify_obs();
	fsm->s_game_start = false;
	fsm->start_game = true;
	fsm->notify_obs();
	fsm->start_game = false;
}

void ask_for_name(void* data) {
	FSM * fsm = (FSM*)data;
	fsm->s_name = true;
	fsm->notify_obs();
	fsm->s_name = false;
}
void check_map_and_save_send_ack(void*data) {
	FSM * fsm = (FSM*)data;

	fsm->check_map = true;
	fsm->notify_obs();
	fsm->check_map = false;

	if(!fsm->error_ocurred) //the map is valid, I should send an ACK
		send_ack(data);
}
void send_map_is(void * data) { 
	FSM * fsm = (FSM*)data;

	fsm->ld_new_map = true;
	fsm->notify_obs();
	fsm->ld_new_map = false;

	fsm->s_map_is = true;
	fsm->notify_obs();
	fsm->s_map_is = false;
	set_ack_time_out(data);
}
void load_enemy_action_and_send_ack(void*data) {


	load_enemy_action(data);
	send_ack(data);
}

void load_enemy_action(void*data) {

	FSM * fsm = (FSM*)data;

	fsm->ld_enemy_action = true;
	fsm->notify_obs();
	fsm->ld_enemy_action = false;
}

void load_action_and_send_it_back(void * data) {
	
	FSM * fsm = (FSM*)data;
	fsm->check_action = true;
	fsm->notify_obs();
	fsm->check_action = false;
	fsm->s_action_from_action_request = true;
	fsm->notify_obs();
	fsm->s_action_from_action_request = false;

	set_ack_time_out(data);
}
void start_game_and_send_ack(void*data) {
	FSM * fsm = (FSM*)data;
	fsm->start_game = true;
	fsm->notify_obs();
	fsm->start_game = false;

	execute_saved_enemy_actions(data);
	send_ack(data);
}
void set_ack_time_out(void*data) {
	FSM * fsm = (FSM*)data;
	fsm->new_ack_time_out = true;
	fsm->notify_obs();
	fsm->new_ack_time_out = true;
}
void send_ack(void * data) {
	FSM * fsm = (FSM*)data;
	fsm->s_ack = true;
	fsm->notify_obs();
	fsm->s_ack = false;
}

void copy_event(edge_t* to_copy, edge_t* to_be_copied, int length) {
	for (int i = 0; i < length; i++)
	{
		to_copy[i].event = to_be_copied[i].event;
		to_copy[i].nextstate = to_be_copied[i].nextstate;
		to_copy[i].fun_trans = to_be_copied[i].fun_trans;
	}
}

EventPackage* FSM::get_fsm_ev_pack() {
	return this->my_ev_pack;
}

edge_t * FSM::give_me_the_actual_state() {

	return this->actual_state;
}

void FSM::load_fsm_ev_pack(EventPackage* event_package_to_be_loaded) {
	 this->my_ev_pack= event_package_to_be_loaded;
}




void execute_action_send_it_and_set_ack_time_out(void * data) {

	FSM* fsm = (FSM*)data;

	fsm->check_action = true;
	fsm->notify_obs();
	fsm->check_action = false;
	fsm->s_action = true;
	fsm->notify_obs();
	fsm->s_action = false;

	set_ack_time_out(data);

}

void execute_receive_action_request_send_action_and_send_ack(void * data) {

	FSM* fsm = (FSM*)data;
	fsm->ex_action = true;
	fsm->notify_obs();
	fsm->ex_action = false;
	fsm->s_action = true;
	fsm->notify_obs();
	fsm->s_action = false;
}

void check_and_send_action_request(void*data) {

	FSM* fsm = (FSM*)data;

	fsm->check_local_action_request = true;
	fsm->notify_obs();
	fsm->check_local_action_request = false;

	if(fsm->valid_local_action_request)
		send_action_request_and_set_ack_time_out(data);

}


void analyze_action_being_client(void* data) {

	FSM * fsm = (FSM*)data;

	if (fsm->get_fsm_ev_pack()->is_this_a_local_action()) //move o attack local del cliente, tengo que mandar action_request
	{
		send_action_request_and_set_ack_time_out(data);
	}
	else
		execute_receive_action_and_send_ack(data);  //move o attack externo, lo paso a ejecutar

}


void execute_receive_action_and_send_ack(void *data) {

	FSM* fsm = (FSM*)data;
	fsm->check_action = true;
	fsm->notify_obs();
	fsm->check_action = false;
	send_ack(data);

}




void check_action_request(void* data) {
	FSM* fsm = (FSM*)data;
	fsm->check_action = true;
	fsm->notify_obs();
	fsm->check_action = false;
}


void send_action_and_set_ack_time_out(void* data){
	FSM* fsm = (FSM*)data;
	fsm->s_action = true;
	fsm->notify_obs();
	fsm->s_action = false;

	set_ack_time_out(data);
}

void execute_action_and_send_ack(void* data) {
	FSM* fsm = (FSM*)data;
	fsm->ex_action = true;
	fsm->notify_obs();
	fsm->ex_action = false;

	send_ack(data);
}

void send_action_request_and_set_ack_time_out(void* data) {
	FSM* fsm = (FSM*)data;
	fsm->valid_local_action_request = false;
	fsm->s_action_request = true;
	fsm->notify_obs();
	fsm->s_action_request = false;
	set_ack_time_out(data);
}

void receive_name_and_send_ack(void*data) {
	FSM* fsm = (FSM*)data;
	fsm->receive_name = true;
	fsm->notify_obs();
	fsm->receive_name = false;
	send_ack(data);
}

void send_next_map(void*data) {  

}

void send_we_won(void*data) {

	FSM* fsm = (FSM*)data;
	fsm->s_we_won = true;
	fsm->notify_obs();
	fsm->s_we_won = false;
}

// Action routine for the client when it´s received an WE_WON package from the server
void analyze_we_won(void*data) {

	FSM* fsm = (FSM*)data;
	fsm->we_won = true;
	fsm->notify_obs();			//analysis of the current game situation if it matchs with a we won situation
	fsm->we_won = false;

	if (!fsm->error_ocurred)
	{
		ask_user_being_client_and_send_decition(data); //By an Allegro interface
		fsm->error_ocurred = false; 
	}
}

// Action routine for the client when it´s received an GAME_OVER package from the server
void analyze_we_lost(void*data) {

	FSM* fsm = (FSM*)data;
	fsm->we_lost = true;
	fsm->notify_obs();			//analysis of the current game situation if it matchs with a we lost situation
	fsm->we_lost = false;

	if (!fsm->error_ocurred)
	{
		ask_user_being_client_and_send_decition(data); //By an Allegro interface
		fsm->error_ocurred = false;
	}

}

void ask_the_user_if_wants_to_play_again(void*data) {

	FSM* fsm = (FSM*)data;
	/*
	if(ALLEGRO INTERFACE)
	{
		fsm->want_to_play_again = true; 
	}
	else
		fsm->want_to_play_again = false; 

	*/
}

void ask_user_being_client_and_send_decition(void*data) { 

	FSM* fsm = (FSM*)data;
	ask_the_user_if_wants_to_play_again(data); //By an Allegro interface
	
	if (fsm->want_to_play_again)
	{
		fsm->s_play_again = true;
		fsm->notify_obs();
		fsm->s_play_again = false;
	}
	else
	{
		fsm->s_game_over = true;
		fsm->notify_obs();
		fsm->s_game_over = false;
	}
	fsm->want_to_play_again = false;

}

void ask_user_being_server_and_send_decition(void*data) {  

	FSM* fsm = (FSM*)data;
	ask_the_user_if_wants_to_play_again(data); //By an Allegro interface

	if (fsm->want_to_play_again)
	{
		fsm->ld_play_again = true;
		fsm->notify_obs();
		fsm->ld_play_again = false;
	}
	else
	{
		fsm->ld_game_over = true;
		fsm->notify_obs();
		fsm->ld_game_over = false;
	}

	fsm->want_to_play_again = false;

}
void tell_user_send_ack_and_finish_game(void*data) {

	FSM* fsm = (FSM*)data;
	/*
	ALLEGRO INTERFACE TO TELL THE USER THE OTHER COMPUTER DOESN´T WANT TO PLAY AGAIN
	*/
	send_ack(data);
	finish_game(data);
}

void send_we_lost(void*data) { //el servidor le avisa a client que se perdió

	FSM* fsm = (FSM*)data;
	fsm->s_game_over = true;
	fsm->notify_obs();
	fsm->s_game_over = false;
}
void send_game_over(void*data) {

	FSM* fsm = (FSM*)data;
	fsm->s_game_over = true;
	fsm->notify_obs();
	fsm->s_game_over = false;
}

void send_play_again(void*data) {
	FSM* fsm = (FSM*)data;
	fsm->s_play_again = true;
	fsm->notify_obs();
	fsm->s_play_again = false;
}

void load_and_send_enemy_action(void*data){
	load_enemy_action(data);
	send_enemy_action(data);
}
 