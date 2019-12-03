#include "LogicFSMRoutines.h"
#include "LogicFSM.h"


void execute_action_send_it_and_set_ack_time_out(void * data) {

	check_action(data);
	execute_local_action(data);
	send_action(data);
	set_ack_time_out(data);
	check_game_state(data);

}

void send_action(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;

	fsm->s_action = true;
	fsm->notify_obs();
	fsm->s_action = false;
}

void execute_receive_action_request_send_action_and_send_ack(void * data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->ex_action = true;
	fsm->notify_obs();
	fsm->ex_action = false;
	fsm->s_action = true;
	fsm->notify_obs();
	fsm->s_action = false;
}

void check_and_send_action_request(void*data) {

	LogicFSM* fsm = (LogicFSM*)data;
	check_action(data);

	if (!fsm->error_ocurred)  //The action request was valid
		send_action_request_and_set_ack_time_out(data);
	else
		fsm->error_ocurred = false; //The action request was invalid

}

void execute_receive_action_and_send_ack(void *data) {

	LogicFSM* fsm = (LogicFSM*)data;
	check_action(data);
	execute_extern_action(data);
	received_ack_routine(data);
	send_ack(data);
}

void check_action(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->check_action = true;			
	fsm->notify_obs();				//LogicFSMSceneObserver
	fsm->check_action = false;
}

void check_game_state(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->check_game_state = true;
	fsm->notify_obs();
	fsm->check_game_state = false;
}

void send_action_and_set_ack_time_out(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->s_action = true;
	fsm->notify_obs();		//FSMCommunicationObserver
	fsm->s_action = false;

	set_ack_time_out(data);
}

void execute_action_and_send_ack(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->ex_action = true;
	fsm->notify_obs();
	fsm->ex_action = false;

	send_ack(data);
}

void send_action_request_and_set_ack_time_out(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->s_action_request = true;
	fsm->notify_obs();				//FSMCommunicationObserver
	fsm->s_action_request = false;
	set_ack_time_out(data);
}

void receive_name_and_send_ack(void*data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->receive_name = true;
	fsm->notify_obs();		//LogicFSMEventsObserver, loads in user data his names
	fsm->receive_name = false;
	send_ack(data);
}

void send_next_map(void*data) {

}

void send_we_won(void*data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->s_we_won = true;
	fsm->notify_obs();
	fsm->s_we_won = false;
}

// Action routine for the client when it´s received an WE_WON package from the server
void analyze_we_won(void*data) {

	LogicFSM* fsm = (LogicFSM*)data;
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

	LogicFSM* fsm = (LogicFSM*)data;
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

	LogicFSM* fsm = (LogicFSM*)data;
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

	LogicFSM* fsm = (LogicFSM*)data;
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

	LogicFSM* fsm = (LogicFSM*)data;
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

	LogicFSM* fsm = (LogicFSM*)data;
	/*
	ALLEGRO INTERFACE TO TELL THE USER THE OTHER COMPUTER DOESN´T WANT TO PLAY AGAIN
	*/
	send_ack(data);
	finish_game(data);
}

void send_we_lost(void*data) { //el servidor le avisa a client que se perdió

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->s_game_over = true;
	fsm->notify_obs();
	fsm->s_game_over = false;
}
void send_game_over(void*data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->s_game_over = true;
	fsm->notify_obs();
	fsm->s_game_over = false;
}

void send_play_again(void*data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->s_play_again = true;
	fsm->notify_obs();
	fsm->s_play_again = false;
}

void load_and_send_enemy_action(void*data) {
	load_enemy_action(data);
	send_enemy_action(data);
}

void do_nothing(void* data)
{

}

void send_name_is(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_name_is = true;
	fsm->notify_obs();	//FSMCommunicationObserver
	fsm->s_name_is = false;
	set_ack_time_out(data);
}


//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
void send_quit(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_quit = true;
	fsm->notify_obs();		//FSMCommunicationObserver
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
	LogicFSM * fsm = (LogicFSM*)data;

	if (((ERROR_EventPackage *)fsm->get_fsm_ev_pack())->is_this_a_local_error())
		send_error_and_finish_game(data);
	else
		finish_game(data);
}

//Se sale del programa sin avisar, rutina de acción del evento ERROR1
void finish_game(void * data) {

	LogicFSM * fsm = (LogicFSM*)data;
	fsm->end_game = true;
	fsm->notify_obs();
	//si bien esto es innecesario a simple vista, lo pongo en false por las dudas que tenga que volver a iniciar el juego desde menu
	fsm->end_game = false;
}

void received_ack_routine(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->reset_ack_timer = true;
	fsm->notify_obs();
	fsm->reset_ack_timer = false;
}

void check_sum_and_send_ack(void* data) {

}

void send_error_and_finish_game(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_error = true;
	fsm->notify_obs();
	fsm->s_error = false;
}

void execute_and_send_enemy_action(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;

	fsm->ex_action = true;
	fsm->notify_obs();
	fsm->ex_action = false;
	send_enemy_action(data);
	set_ack_time_out(data);
	check_game_state(data);
}

void save_enemy_action_and_send_it(void* data) {

	save_enemy_action(data);
	send_enemy_action(data);
}
void execute_saved_enemy_actions(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;

	fsm->ex_saved_enemy_actions = true;
	fsm->notify_obs();				//LogicFSMSceneObserver
	fsm->ex_saved_enemy_actions = false;
}

void execute_local_action(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;

	if (fsm->error_ocurred)
		fsm->valid_local_action = false;
	else
		fsm->valid_local_action = true;


	fsm->ex_action = true;
	fsm->notify_obs();
	fsm->ex_action = false;

}

void execute_extern_action(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;

	if (fsm->error_ocurred)
		fsm->valid_extern_action = false;
	else
		fsm->valid_extern_action = true;


	fsm->ex_action = true;
	fsm->notify_obs();
	fsm->ex_action = false;
}

void save_enemy_action(void* data) {

	LogicFSM * fsm = (LogicFSM*)data;

	fsm->sv_enemy_action = true;
	fsm->notify_obs();
	fsm->sv_enemy_action = false;
}

void send_enemy_action(void* data) {

	LogicFSM * fsm = (LogicFSM*)data;

	fsm->s_enemy_action = true;
	fsm->notify_obs();
	fsm->s_enemy_action = false;
}

void send_game_start(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_game_start = true;
	fsm->notify_obs();		//FSMCommunicationObserver
	fsm->s_game_start = false;
	fsm->start_game = true;
	fsm->notify_obs();		//LogicFSMSceneObserver, GraphicGameFSM, LogicFSMGraphicEventsObserver
	fsm->start_game = false;
}

void ask_for_name(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_name = true;
	fsm->notify_obs();		//FSMCommunicationObserver
	fsm->s_name = false;
}
void check_map_and_save_send_ack(void*data) {
	LogicFSM * fsm = (LogicFSM*)data;

	fsm->check_map = true;
	fsm->notify_obs();
	fsm->check_map = false;

	if (!fsm->error_ocurred) //the map is valid, I should send an ACK
		send_ack(data);
}
void send_map_is(void * data) {
	LogicFSM * fsm = (LogicFSM*)data;

	fsm->ld_new_map = true;
	fsm->notify_obs();
	fsm->ld_new_map = false;

	fsm->s_map_is = true;
	fsm->notify_obs();
	fsm->s_map_is = false;
	set_ack_time_out(data);
}
void load_enemy_action_and_send_ack(void*data) {

	LogicFSM * fsm = (LogicFSM*)data;
	check_action(data);

	if (fsm->error_ocurred)
		fsm->valid_extern_action = false;
	else
		fsm->valid_extern_action = true;


	load_enemy_action(data);
}

void load_enemy_action(void*data) {

	LogicFSM * fsm = (LogicFSM*)data;

	if (fsm->error_ocurred)
		execute_extern_action(data);
	else
	{
		fsm->ld_enemy_action = true;
		fsm->notify_obs();
		fsm->ld_enemy_action = false;
		send_ack(data);
	}
}

void load_action_and_send_it_back(void * data) {

	LogicFSM * fsm = (LogicFSM*)data;

	check_action(data);
	execute_extern_action(data);

	fsm->s_action_from_action_request = true;
	fsm->notify_obs();
	fsm->s_action_from_action_request = false;

	set_ack_time_out(data);
	check_game_state(data);
}

void start_game_and_send_ack(void*data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->start_game = true;
	fsm->notify_obs();
	fsm->start_game = false;

	execute_saved_enemy_actions(data);
	send_ack(data);
}
void set_ack_time_out(void*data) {
	LogicFSM * fsm = (LogicFSM*)data;
	//FALTA IMPLEMENTAR
	fsm->new_ack_time_out = true;
	fsm->notify_obs();		//FSMCommunicationObserver
	fsm->new_ack_time_out = true;
}
void send_ack(void * data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->s_ack = true;
	fsm->notify_obs();		//FSMCommunicationObserver
	fsm->s_ack = false;
}

