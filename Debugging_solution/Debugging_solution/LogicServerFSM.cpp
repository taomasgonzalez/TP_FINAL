#include "LogicServerFSM.h"


void do_nothing(void * data);//Dummy for the debugging of the protocol structure
void do_nothing(void * data) {

}

void finish_game(void * data);
//Se sale del programa sin avisar, rutina de acción del evento ERROR1
void finish_game(void * data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->end_game = true;
	fsm->notify_obs();
	//si bien esto es innecesario a simple vista, lo pongo en false por las dudas que tenga que volver a iniciar el juego desde menu
	fsm->end_game = false;
}

void set_ack_time_out(void* data);
void set_ack_time_out(void*data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->new_ack_time_out = true;
	fsm->notify_obs();
	fsm->new_ack_time_out = true;
}

void send_error_and_finish_game(void* data);
void send_error_and_finish_game(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_error = true;
	fsm->notify_obs();
	fsm->s_error = false;
}

//analyze
void analayze_error(void*data);
void analayze_error(void*data)
{
	LogicFSM * fsm = (LogicFSM*)data;

	if (((ERROR_EventPackage *)fsm->get_fsm_ev_pack())->is_this_a_local_error())
		send_error_and_finish_game(data);
	else
		finish_game(data);
}

//send
void send_ack(void * data);
void send_ack(void * data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_ack = true;
	fsm->notify_obs();
	fsm->s_ack = false;
}

void send_quit(void * data);
//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
void send_quit(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_quit = true;
	fsm->notify_obs();
	fsm->s_quit = false;
	set_ack_time_out(data);

}

void send_ack_and_quit(void* data);
//se devuelve un ACK con ID 0 para la otra compu, se sale
void send_ack_and_quit(void* data) {

	//Interfaz del usuario avisando la situación
	send_ack(data);
	finish_game(data);
}

//others
void ask_for_name(void* data);
void ask_for_name(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_name = true;
	fsm->notify_obs();
	fsm->s_name = false;
}

LogicServerFSM::LogicServerFSM(Userdata * data) : LogicFSM(data)
{
	edge_t *Initial_state_aux = new edge_t[5];
	this->Initial_state = Initial_state_aux;

	edge_t Initial_state[5] =
	{
		{ Event_type::START_COMMUNICATION, this->Naming_him_state, ask_for_name },
	{ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }, //se recibe un envio un quit local, paso a esperar el ACK
	{ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }, //se recibe un quit por networking,
	{ Event_type::ERROR1, NULL, analayze_error },
	{ Event_type::END_OF_TABLE, this->Initial_state, do_nothing }
	};
	copy_event(Initial_state_aux, Initial_state, 5);

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

