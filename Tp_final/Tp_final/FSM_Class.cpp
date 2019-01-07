/*******************************************************************************
                      INCLUDED HEADERS a
******************************************************************************/
#include "FSM_Class.h"
void copy_event(edge_t to_copy[], edge_t to_be_copied[], int length);

void do_nothing(void * data);//Dummy for the debugging of the protocol structure
void send_map_is(void * data);
void send_ack(void * data);
void received_ack_routine(void* data);
void send_quit(void * data);

void load_enemy_action(void* data);
void check_action_request(void* data);
void ask_for_name(void* data);
void send_name_is(void* data);
void send_ack_and_quit(void* data);
void check_map_and_save(void* data);
void send_enemy_action(void* data);
void send_game_start(void* data);
void finish_game(void * data);
void send_error_and_finish_game(void* data);
void check_sum_and_send_ack(void* data);
void load_action_and_send_ack(void* data);
void start_game_and_send_ack(void* data);
void set_ack_time_out(void* data);
void send_action_and_set_ack_time_out(void* data);


/*******************************************************************************
							FSM CONSTRCUTOR
******************************************************************************/

Fsm::Fsm(bool is_client) : Observable(){
	this->ev_pack = new EventPackage();

	waiting_for_ack = false;
	reset_ack_timer = false;
	new_ack_time_out = false;

	ask_name = false;
	s_quit = false;
	s_ack = false;
	s_name_is = false;
	s_error = false;
	s_map_is = false;
	end_game = false;
	s_game_start = false;
	s_enemy_action = false;
	s_action_request = false;
	s_action = false;
	start_game = false;
	check_action = false;
	execute_action = false;
	receive_name = false;


	if (is_client) 
		init_fsm_client();
	else 
		init_fsm_server();

}


/*******************************************************************************
                           FSM_SERVER CONSTRCUTOR
******************************************************************************/

void Fsm::init_fsm_server(){

	edge_t * Initial_state_aux = new edge_t[6];
	this->Initial_state = Initial_state_aux;

	edge_t * Naming_him_state_aux = new edge_t[6];
	this->Naming_him_state = Naming_him_state_aux;

	edge_t* Naming_me_state_aux = new edge_t[6];
	this->Naming_me_state = Naming_me_state_aux;

	edge_t * Waiting_for_ACK_name_state_aux = new edge_t[6];
	this->Waiting_for_ACK_name_state = Waiting_for_ACK_name_state_aux;

	edge_t * Waiting_for_ACK_state_aux = new edge_t[4];
	this->Waiting_for_ACK_state = Waiting_for_ACK_state_aux;

	edge_t * Waiting_for_ACK_quit_state_aux = new edge_t[4];
	this->Waiting_for_ACK_quit_state = Waiting_for_ACK_quit_state_aux;

	edge_t* Waiting_for_ACK_map_state_aux = new edge_t [6];
	this->Waiting_for_ACK_map_state = Waiting_for_ACK_map_state_aux;

	edge_t* Waiting_for_ACK_enemy_actions_state_aux = new edge_t[7];
	this->Waiting_for_ACK_enemy_actions_state = Waiting_for_ACK_enemy_actions_state_aux;

	edge_t * Playing_state_aux = new edge_t[11];
	this->Playing_state = Playing_state_aux;

	edge_t* Waiting_for_ACK_game_start_state_aux = new edge_t[6];
	this->Waiting_for_ACK_game_start_state = Waiting_for_ACK_game_start_state_aux;

	edge_t Initial_state[6] =
	{
		{ Event::START_COMMUNICATION, this->Naming_him_state, ask_for_name },
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Initial_state, do_nothing }
	};
	copy_event(Initial_state_aux, Initial_state, 6);

	edge_t Naming_him_state[6] =
	{
		{ Event::NAME_IS, this->Naming_me_state, receive_name_and_send_ack }, //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Naming_him_state, do_nothing }
	};
	copy_event(Naming_him_state_aux, Naming_him_state, 6);

	edge_t Naming_me_state[6] =
	{
		{ Event::NAME, this->Waiting_for_ACK_map_state, send_name_is }, //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Naming_me_state, do_nothing }
	};
	copy_event(Naming_me_state_aux, Naming_me_state, 6);

	edge_t  Waiting_for_ACK_name_state[6] =
	{
		{ Event::ACK, this->Waiting_for_ACK_map_state, send_map_is },
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Waiting_for_ACK_name_state, do_nothing }
	};
	copy_event(Waiting_for_ACK_name_state_aux, Waiting_for_ACK_name_state, 6);

	edge_t Waiting_for_ACK_map_state[6] =
	{
		{ Event::ACK, this->Waiting_for_ACK_enemy_actions_state, send_enemy_action },
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Waiting_for_ACK_map_state, do_nothing }
	};
	copy_event(Waiting_for_ACK_map_state_aux, Waiting_for_ACK_map_state, 6);

	edge_t Waiting_for_ACK_enemy_actions_state[7] =
	{
		{ Event::ACK, this->Waiting_for_ACK_enemy_actions_state, send_enemy_action },
	{Event::ENEMY_ACTION_IS_OK, this->Waiting_for_ACK_game_start_state, send_game_start},
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Waiting_for_ACK_enemy_actions_state, do_nothing }
	};

	copy_event(Waiting_for_ACK_enemy_actions_state_aux, Waiting_for_ACK_enemy_actions_state, 7);

	edge_t Waiting_for_ACK_game_start_state[6] =
	{
		{ Event::ACK, this->Playing_state, do_nothing },
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Waiting_for_ACK_game_start_state, do_nothing }
	};

	copy_event(Waiting_for_ACK_game_start_state_aux, Waiting_for_ACK_game_start_state, 6);

	edge_t Playing_state[11] =
	{
		{Event::LOCAL_ENEMY_ACTION, this->Playing_state, load_and_send_enemy_action},
	{Event::EXTERN_ACTION_REQUESTED, this->Playing_state, check_action_request },
	{ Event::EXTERN_ACTION_ACCEPTED, this->Playing_state, execute_send_action_and_set_ack_time_out },
	{ Event::EXTERN_ACTION_DENIED, this->Playing_state, do_nothing}, 
	{Event::LOCAL_ACTION_REQUESTED, this->Playing_state, check_action_request}
	{ Event::LOCAL_ACTION, this->Playing_state, execute_send_action_and_set_ack_time_out},
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, 
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Playing_state_aux, Playing_state, 11);

	edge_t Waiting_for_ACK_quit_state[4] =
	{
		{ Event::ACK, NULL, finish_game },
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Waiting_for_ACK_quit_state, do_nothing }
	};

	copy_event(Waiting_for_ACK_quit_state_aux, Waiting_for_ACK_quit_state, 4);

	this->actual_state = this->Initial_state;


}


/*******************************************************************************
FSM_CLIENT CONSTRCUTOR
******************************************************************************/
void Fsm::init_fsm_client() {

	edge_t * Initial_state_aux = new edge_t[6];
	this->Initial_state = Initial_state_aux;

	edge_t * Naming_him_state_aux = new edge_t[6];
	this->Naming_him_state = Naming_him_state_aux;

	edge_t* Naming_me_state_aux = new edge_t[6];
	this->Naming_me_state = Naming_me_state_aux;

	edge_t * Waiting_for_ACK_state_aux = new edge_t[4];
	this->Waiting_for_ACK_state = Waiting_for_ACK_state_aux;

	edge_t * Waiting_for_ACK_quit_state_aux = new edge_t[4];
	this->Waiting_for_ACK_quit_state = Waiting_for_ACK_quit_state_aux;

	edge_t* Waiting_for_map_state_aux = new edge_t[7];
	this->Waiting_for_map_state = Waiting_for_map_state_aux;

	edge_t* Waiting_for_enemy_actions_state_aux = new edge_t[7];
	this->Waiting_for_enemy_actions_state = Waiting_for_enemy_actions_state_aux;

	edge_t * Playing_state_aux = new edge_t[7];
	this->Playing_state = Playing_state_aux;

	edge_t* Waiting_for_game_start_state_aux = new edge_t[6];
	this->Waiting_for_game_start_state = Waiting_for_game_start_state_aux;

	edge_t Initial_state[6] =
	{
		{ Event::NAME, this->Naming_me_state,  send_name_is}, 
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Initial_state, do_nothing }
	};
	copy_event(Initial_state_aux, Initial_state, 6);

	edge_t Naming_me_state[6] =
	{
		{ Event::ACK, this->Naming_him_state, ask_for_name }, //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Naming_me_state, do_nothing }
	};
	copy_event(Naming_me_state_aux, Naming_me_state, 6);

	edge_t Naming_him_state[6] =
	{
		{ Event::NAME_IS, this->Naming_me_state, receive_name_and_send_ack }, //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Naming_him_state, do_nothing }
	};
	copy_event(Naming_him_state_aux, Naming_him_state, 6);

	edge_t  Waiting_for_map_state[7] =
	{
		{ Event::MAP_IS, this->Waiting_for_ACK_map_state, check_map_and_save },
	{ Event::MAP_IS_OK, this->Waiting_for_enemy_actions_state, do_nothing},
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Waiting_for_map_state, do_nothing }
	};
	copy_event(Waiting_for_map_state_aux, Waiting_for_map_state, 7);


	edge_t Waiting_for_enemy_actions_state[7] =
	{
		{ Event::EXTERN_ENEMY_ACTION, this->Waiting_for_enemy_actions_state, load_action_and_send_ack },
	{ Event::ENEMY_ACTION_IS_OK, this->Waiting_for_game_start_state, load_action_and_send_ack },
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Waiting_for_enemy_actions_state, do_nothing }
	};

	copy_event(Waiting_for_enemy_actions_state_aux, Waiting_for_enemy_actions_state, 7);

	edge_t Waiting_for_game_start_state[6] =
	{
		{ Event::GAME_START, this->Playing_state, start_game_and_send_ack },
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Waiting_for_game_start_state, do_nothing }
	};

	copy_event(Waiting_for_game_start_state_aux, Waiting_for_game_start_state, 6);

	edge_t Playing_state[7] =
	{
		{Event::EXTERN_ENEMY_ACTION, this->Playing_state, load_action_and_send_ack},
	{ Event::LOCAL_ACTION, this->Playing_state, send_action_request_and_set_ack_time_out }, 
	{ Event::EXTERN_ACTION_RECEIVED, this->Playing_state, execute_action_and_send_ack }, 
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, 
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Playing_state_aux, Playing_state, 7);

	edge_t Waiting_for_ACK_quit_state[4] =
	{
		{ Event::ACK, NULL, finish_game },
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Waiting_for_ACK_state, do_nothing }
	};

	copy_event(Waiting_for_ACK_quit_state_aux, Waiting_for_ACK_quit_state, 4);

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
void Fsm:: run_fsm(EventPackage ev_pack)
{
	Event event1 = ev_pack.ev;
	*this->ev_pack = ev_pack;

	while ((this->actual_state->event != event1) && (this->actual_state->event != Event::END_OF_TABLE))
	{	
		this->actual_state++;
	}

	//genera evento de software en caso de haber encontrado un evento que no debería ocurrir en ese estado.s
	//if (this->actual_state->event == Event::END_OF_TABLE) 
	//	this->check_for_incorrect_event(event1);			

	//Runs the functions related to that event
	(this->actual_state->fun_trans)(this);
	this->actual_state = (this->actual_state->nextstate);


}

void Fsm::check_for_incorrect_event(Event event) {
	//if(this->actual_state == this->Waiting..) {

	//}
}

void Fsm::init_fsm()
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
	Fsm * fsm = (Fsm*)data;
	fsm->s_name_is = true;
	fsm->notify_obs();
	fsm->s_name_is = false;
	set_ack_time_out(data);
 }

 //se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
 void send_quit(void* data) {
	 Fsm * fsm = (Fsm*)data;
	 fsm->s_quit = true;
	 fsm->notify_obs();
	 set_ack_time_out(data);
}

 //se devuelve un ACK con ID 0 para la otra compu, se sale
 void send_ack_and_quit(void* data) {
	 send_ack(data);
	 finish_game(data);
}


 //Se sale del programa sin avisar, rutina de acción del evento ERROR1
void finish_game(void * data) {
	Fsm * fsm = (Fsm*)data;
	fsm->end_game = true;
	fsm->notify_obs();

	//si bien esto es innecesario a simple vista, lo pongo en false por las dudas que tenga que volver a iniciar el juego desde menu
	fsm->end_game = false;
}

void received_ack_routine(void* data) {
	Fsm * fsm = (Fsm*)data;
	fsm->reset_ack_timer = true;
	fsm->notify_obs();
	fsm->reset_ack_timer = false;
}

void check_sum_and_send_ack(void* data) {

}

void send_error_and_finish_game(void* data) {
	Fsm * fsm = (Fsm*)data;
	fsm->s_error = true;
	fsm->notify_obs();
	fsm->s_error = false;
}

void send_enemy_action(void* data) {
	Fsm * fsm = (Fsm*)data;
	fsm->s_enemy_action = true;
	fsm->notify_obs();
	fsm->s_enemy_action = false;
}

void send_game_start(void* data) {
	Fsm * fsm = (Fsm*)data;
	fsm->s_game_start = true;
	fsm->notify_obs();
	fsm->s_game_start = false;
}

void ask_for_name(void* data) {
	Fsm * fsm = (Fsm*)data;
	fsm->ask_name = true;
	fsm->notify_obs();
	fsm->ask_name = false;
}
void check_map_and_save(void*data) {

}
void load_action_and_send_ack(void*data) {
	load_enemy_action(data);
	send_ack(data);
}
void load_enemy_action(void * data) {

}
void start_game_and_send_ack(void*data) {
	Fsm * fsm = (Fsm*)data;
	fsm->start_game = true;
	fsm->notify_obs();
	fsm->start_game = false;
	send_ack(data);
}
void set_ack_time_out(void*data) {
	Fsm * fsm = (Fsm*)data;
	fsm->new_ack_time_out = true;
	fsm->notify_obs();
	fsm->new_ack_time_out = true;
}
void send_ack(void * data) {
	Fsm * fsm = (Fsm*)data;
	fsm->s_ack = true;
	fsm->notify_obs();
	fsm->s_ack = false;
}
void send_map_is(void * data) {
	Fsm * fsm = (Fsm*)data;
	fsm->s_map_is = true;
	fsm->notify_obs();
	fsm->s_map_is = false;
	set_ack_time_out(data);
}
void copy_event(edge_t* to_copy, edge_t to_be_copied[], int length) {
	for (int i = 0; i < length; i++)
	{
		to_copy[i].event = to_be_copied[i].event;
		to_copy[i].nextstate = to_be_copied[i].nextstate;
		to_copy[i].fun_trans = to_be_copied[i].fun_trans;
	}
}

EventPackage* Fsm::get_fsm_ev_pack() {
	return this->ev_pack;
}

void check_action_request(void* data) {
	Fsm* fsm = (Fsm*)data;
	fsm->check_action = true;
	fsm->notify_obs();
	fsm->check_action = false;
}


void send_action_and_set_ack_time_out(void* data){
	Fsm* fsm = (Fsm*)data;
	fsm->s_action = true;
	fsm->notify_obs();
	fsm->s_action = false;

	set_ack_time_out(data);
}

void execute_send_action_and_set_ack_time_out(void* data) {

	Fsm* fsm = (Fsm*)data;
	fsm->execute_action = true;
	fsm->notify_obs();
	fsm->execute_action = false;
	fsm->s_action = true;
	fsm->notify_obs();
	fsm->s_action = false;

	set_ack_time_out(data);
}
void execute_action_and_send_ack(void* data) {
	Fsm* fsm = (Fsm*)data;
	fsm->execute_action = true;
	fsm->notify_obs();
	fsm->execute_action = false;

	send_ack(data);
}

void send_action_request_and_set_ack_time_out(void* data) {
	Fsm* fsm = (Fsm*)data;
	fsm->s_action_request = true;
	fsm->notify_obs();
	fsm->s_action_request = false;
	set_ack_time_out(data);
}

void receive_name_and_send_ack(void*data) {
	Fsm* fsm = (Fsm*)data;
	fsm->receive_name = true;
	fsm->notify_obs();
	fsm->receive_name = false;
	send_ack(data);
}

void load_and_send_enemy_action(void*data){
	load_enemy_action(data);
	send_enemy_action(data);
}