/*******************************************************************************
                      INCLUDED HEADERS a
******************************************************************************/
#include "FSM_Class.h"
void copy_event(edge_t to_copy[], edge_t to_be_copied[], int length);

void do_nothing(void *);//Dummy for the debugging of the protocol structure
void send_map_is(void *);
void send_ack(void *);
void received_ack_routine(void* data);
void send_quit(void *);
void send_action(void *);

void ask_for_name(void*);
void send_name_is(void*);
void send_ack_and_quit(void*);
void check_map_and_save(void*);
void send_enemy_action(void*);
void send_game_start(void*);
void finish_game(void *);
void send_error_and_finish_game(void*);
void check_sum_and_send_ack(void*);
void load_action_and_send_ack(void*);
void start_game_and_send_ack(void*);
void set_ack_time_out(void*);

/*******************************************************************************
							FSM CONSTRCUTOR
******************************************************************************/

Fsm::Fsm(bool is_client) : Observable(){

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

	edge_t * Playing_state_aux = new edge_t[8];
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
		{ Event::NAME_IS, this->Naming_me_state, send_ack }, //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
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

	edge_t Playing_state[8] =
	{
		{ Event::EXTERN_ACTION_ACCEPTED, this->Playing_state, set_ack_time_out },
	{ Event::EXTERN_ACTION_DENIED, this->Playing_state, do_nothing}, 
	{ Event::LOCAL_ACTION, this->Playing_state, set_ack_time_out},
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, 
	{ Event::LOCAL_ERROR, NULL, send_error_and_finish_game },
	{ Event::EXTERN_ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Playing_state, do_nothing }
	};

	copy_event(Playing_state_aux, Playing_state, 8);

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
		{ Event::START_COMMUNICATION, this->Naming_me_state, send_im_ready }, 
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
		{ Event::ENEMY_ACTION, this->Waiting_for_enemy_actions_state, load_action_and_send_ack },
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
		{ Event::LOCAL_ACTION, this->Playing_state, do_nothing }, 
	{ Event::EXTERN_ACTION_RECEIVED, this->Playing_state, send_ack }, 
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
	this->ev_pack = ev_pack;

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
	/*
	edge_t * Waiting_for_Event_state_aux = new edge_t[7];

	edge_t w_for_e_s[7] =
	{
	{ Event::LOCAL_MOVE, this->Waiting_for_ACK_state, send_move }, //Evento generado por allegro, se manda un MOVE  por networking, se pasa al estado Waiting for ACK
	{ Event::EXTERN_MOVE, this->Waiting_for_Event_state, send_ack_move }, //Evento que llega por networking, se manda ACK y sigue todo igual
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE, this->Waiting_for_Event_state, do_nothing }
	};
	copy_event(Waiting_for_Event_state_aux, w_for_e_s, 7);
	this->Waiting_for_Event_state = Waiting_for_Event_state_aux;


	edge_t * Waiting_for_ACK_state_aux = new edge_t[11];
	edge_t Waiting_for_ACK_state[11] =
	{
		{ Event::TIME_OUT_MOVE, this->Waiting_for_ACK_state, send_move },
	{ Event::TIME_OUT_QUIT, this->Waiting_for_ACK_state, send_quit },
	{ Event::EXTERN_MOVE, this->Waiting_for_ACK_state, send_ack_move }, //Evento que llega por networking, se manda ACK y sigue todo igual
	{ Event::VALID_ACKCODE, this->Waiting_for_Event_state, received_ack_routine },
	{ Event::INVALID_ACKCODE, NULL, finish_game },
	{ Event::TIME_OUT_2, NULL, finish_game },
	{ Event::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit },//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
	{ Event::EXTERN_QUIT, NULL, send_ack_and_quit }, //se devuelve un ACK con ID 0 para la otra compu, se sale
	{ Event::ERROR, NULL, finish_game },
	{ Event::END_OF_TABLE,this->Waiting_for_ACK_state, do_nothing }
	};
	copy_event(Waiting_for_ACK_state_aux, Waiting_for_ACK_state, 11);
	this->Waiting_for_ACK_state = Waiting_for_ACK_state_aux;
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


 //Se envia un MOVE por networking
 void send_action(void * data) {
	 Fsm * fsm = (Fsm*)data;
	 fsm->s_name_is = true;
	 fsm->notify_obs();
	 fsm->s_name_is = false;
	 set_ack_time_out(data);
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
	fsm->set_time_out_tick(false);
	fsm->notify_obs();
	
}

void check_sum_and_send_ack(void* data) {

}

void send_error_and_finish_game(void* data) {
	Fsm * fsm = (Fsm*)data;
	fsm->s_error = true;
	fsm->notify_obs();
	fsm->s_error = false;
}

void send_enemy_action(void*) {
	Fsm * fsm = (Fsm*)data;
	fsm->s_enemy_action = true;
	fsm->notify_obs();
	fsm->s_enemy_action = false;
}

void send_game_start(void* data) {

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
	//faltan cosas aca!
	send_ack(data);
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
	fsm->waiting_for_ack = true;
	fsm->notify_obs();
	fsm->waiting_for_ack = false;
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
	set_ack_time_out();
}
void copy_event(edge_t* to_copy, edge_t to_be_copied[], int length) {
	for (int i = 0; i < length; i++)
	{
		to_copy[i].event = to_be_copied[i].event;
		to_copy[i].nextstate = to_be_copied[i].nextstate;
		to_copy[i].fun_trans = to_be_copied[i].fun_trans;
	}
}

EventPackage Fsm::get_fsm_ev_pack() {
	return this->ev_pack;
}


