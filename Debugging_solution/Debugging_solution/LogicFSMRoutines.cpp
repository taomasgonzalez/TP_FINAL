#include "LogicFSM.h"

//Se sale del programa sin avisar, rutina de acción del evento ERROR1
void finish_game(void * data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->end_game = true;
	fsm->notify_obs();
	//si bien esto es innecesario a simple vista, lo pongo en false por las dudas que tenga que volver a iniciar el juego desde menu
	fsm->end_game = false;
}

void set_ack_time_out(void*data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->new_ack_time_out = true;
	fsm->notify_obs();
	fsm->new_ack_time_out = true;
}

void send_error_and_finish_game(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_error = true;
	fsm->notify_obs();
	fsm->s_error = false;
}

void analayze_error(void*data)
{
	LogicFSM * fsm = (LogicFSM*)data;

	if (((ERROR_EventPackage *)fsm->get_fsm_ev_pack())->is_this_a_local_error())
		send_error_and_finish_game(data);
	else
		finish_game(data);
}

void send_ack(void * data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_ack = true;
	fsm->notify_obs();
	fsm->s_ack = false;
}

//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
void send_quit(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
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

void ask_for_name(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_name = true;
	fsm->notify_obs();
	fsm->s_name = false;
}

void do_nothing(void* data) {
	printf("nothing");
}