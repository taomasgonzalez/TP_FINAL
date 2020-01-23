#include "LogicFSM.h"


LogicFSM::LogicFSM(Userdata* data, LogicEventGenerator *event_gen, Scene* scene, Communication* com):FSM() {
	user_data = data;
	ev_gen = event_gen;
	scenario = scene;
	this->com = com;
}
LogicFSM::~LogicFSM() {

}

/******************************************
***************start_playing************
*******************************************
*Setter: sets we_are_playing of LogicEventGenerator to true.
*/
void LogicFSM::start_playing() {

	ev_gen->are_we_playing = true;
}

/******************************************
***************finish_playing************
*******************************************
*Setter: sets we_are_playing to false.
*/
void LogicFSM::finish_playing() {

	ev_gen->are_we_playing = false;

}


void LogicFSM::run_fsm(EventPackage * ev_pack) {
	if(ev_pack != NULL)
		print_curr_state();
	FSM::run_fsm(ev_pack);
	
	Package * new_pack = com->receiveMessage();

	if (new_pack != NULL) //me un mensaje
	{
		EventPackage * new_event_package = pack_factory.package_2_event_package(new_pack); //convierto el paquete a EventPackage
		ev_gen->append_new_event(new_event_package, (int)(LogicEventGenerator::LogicQueues::net)); //lo meto en la cola
	}

	scenario->control_all_actions();
}

void execute_action_send_it_and_set_ack_time_out_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->execute_action_send_it_and_set_ack_time_out();
}

void send_action_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->send_action();
}

void execute_receive_action_request_send_action_and_send_ack_r(void* data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->execute_receive_action_request_send_action_and_send_ack();
}

void check_and_send_action_request_r(void* data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->check_and_send_action_request();
}

void execute_receive_action_and_send_ack_r(void *data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->execute_receive_action_and_send_ack();
}

void check_action_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->check_action();
}

void check_game_state_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->check_game_state();
}

void send_action_and_set_ack_time_out_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->send_action_and_set_ack_time_out();
}

void execute_action_and_send_ack_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->execute_action_and_send_ack();
}

void send_action_request_and_set_ack_time_out_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->send_action_request_and_set_ack_time_out();
}

void receive_name_and_send_ack_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->receive_name_and_send_ack();
}

void send_next_map_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->send_next_map();
}

void send_we_won_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->send_we_won();
}

// Action routine for the client when it´s received an WE_WON package from the server
void analyze_we_won_r(void* data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->analyze_we_won();
}

// Action routine for the client when it´s received an GAME_OVER package from the server
void analyze_we_lost_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->analyze_we_lost();
}
void ask_the_user_if_wants_to_play_again_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->ask_the_user_if_wants_to_play_again();
}
void ask_user_being_client_and_send_decition_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->ask_user_being_client_and_send_decition();
}
void ask_user_being_server_and_send_decition_r(void* data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->ask_user_being_server_and_send_decition();

}
void tell_user_send_ack_and_finish_game_r(void* data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->tell_user_send_ack_and_finish_game();
}
void send_we_lost_r(void* data) { //el servidor le avisa a client que se perdió
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->send_we_lost();
}
void send_game_over_r(void* data) {

	LogicFSM* fsm = (LogicFSM*)data;
	fsm->send_game_over();
}
void send_play_again_r(void* data) {
	LogicFSM* fsm = (LogicFSM*)data;
	fsm->send_play_again();
}
void load_and_send_enemy_action_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->load_and_send_enemy_action();
}
void do_nothing_r(void* data)
{

}

void reset_game_r(void* data)
{
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->reset_game();
}
void send_name_is_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->send_name_is();
}
//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
void send_quit_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->send_quit();
}
void send_ack_and_quit_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->send_ack_and_quit();
}
void analayze_error_r(void* data)
{
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->analayze_error();
}
//Se sale del programa sin avisar, rutina de acción del evento ERROR1
void finish_game_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->finish_game();
}
void received_ack_routine_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;

	fsm->received_ack_routine();
}
void check_sum_and_send_ack_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->check_sum_and_send_ack();
}
void send_error_and_finish_game_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->send_error_and_finish_game();
}
void execute_and_send_enemy_action_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->execute_and_send_enemy_action();
}
void save_enemy_action_and_send_it_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->save_enemy_action_and_send_it();
}
void execute_saved_enemy_actions_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->execute_saved_enemy_actions();
	fsm->start_playing();
}
void execute_local_action_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->execute_local_action();
}
void execute_extern_action_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->execute_extern_action();
}
void save_enemy_action_r(void* data) {

	LogicFSM * fsm = (LogicFSM*)data;
	fsm->save_enemy_action();	
}
void send_enemy_action_r(void* data) {

	LogicFSM * fsm = (LogicFSM*)data;
	fsm->send_enemy_action();
}
void send_game_start_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->send_game_start();
}
void ask_for_name_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->ask_for_name();
}
void check_map_and_save_send_ack_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->check_map_and_save_send_ack();
}
void send_map_is_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->send_map_is();
}
void load_enemy_action_and_send_ack_r(void* data) {

	LogicFSM * fsm = (LogicFSM*)data;
	fsm->load_enemy_action_and_send_ack();
}
void load_enemy_action(void* data) {

	LogicFSM * fsm = (LogicFSM*)data;
	fsm->load_enemy_action();

}
void load_action_and_send_it_back_r(void* data) {

	LogicFSM * fsm = (LogicFSM*)data;
	fsm->load_action_and_send_it_back();
}
void start_game_and_send_ack_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->start_game_and_send_ack();
}
void set_ack_time_out(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->set_ack_time_out();
}
void send_ack_r(void* data) {
	LogicFSM * fsm = (LogicFSM*)data;
	fsm->send_ack();
}



void LogicFSM::execute_action_send_it_and_set_ack_time_out() {

	check_action();

	
	if (valid_action) {

		//The action is valid so the fetching of allegro events must be blocked for a time gap
		if (!scenario->finished_loading)
		{
			active_blocking_timers(get_fsm_ev_pack());

		}
		else
		{
			//turn_off_blocking_timers(get_fsm_ev_pack());
			scenario->finished_loading = false;
		}

		//The action is not a future event so it must be executed immediately
		if (!scenario->appended_event&&scenario->saved_events->empty()) 
		{
			//execute_local_action();
			std::cout << "Se mando acción" << std::endl;
			send_action();
			set_ack_time_out();
			//check_game_state();
		}
		//Is a future action so the FSM must not move to waiting_for_ACK state
		else
		{
			std::cout << "Se guardo acción" << std::endl;
			should_change_state = false;
			scenario->appended_event = false;
		}



	}
	else 
		should_change_state = false;

}

void LogicFSM::active_blocking_timers(EventPackage * my_package) {
	
	std::cout << "Se activaron los timers" << std::endl;

	if(my_package->give_me_your_event_type()==Event_type::MOVE)

		if(((MOVE_EventPackage *)my_package)->give_me_your_direction()==Direction_type::Left || ((MOVE_EventPackage *)my_package)->give_me_your_direction() == Direction_type::Right)
			this->ev_gen->active_blocking_timers(Blocking_timer_type::Walking);
		else
			this->ev_gen->active_blocking_timers(Blocking_timer_type::Jumping);

	if (my_package->give_me_your_event_type() == Event_type::ATTACK)
	 if (((ATTACK_EventPackage *)my_package)->give_me_your_event_type() == Event_type::ATTACK)
		this->ev_gen->active_blocking_timers(Blocking_timer_type::Attacking);

	//else if (my_package->give_me_your_direction() == Direction_type::Jump_Left || my_package->give_me_your_direction() == Direction_type::Jump_Right || my_package->give_me_your_direction() == Direction_type::Jump_Straight)
	//	this->ev_gen->active_blocking_timers(Blocking_timer_type::Jumping);


}

void LogicFSM::turn_off_blocking_timers(EventPackage * my_package) {

	std::cout << "Se apagaron los timers" << std::endl;

	if (my_package->give_me_your_event_type() == Event_type::MOVE)

		if (((MOVE_EventPackage *)my_package)->give_me_your_direction() == Direction_type::Left || ((MOVE_EventPackage *)my_package)->give_me_your_direction() == Direction_type::Right)
			this->ev_gen->turn_off_blocking_timers(Blocking_timer_type::Walking);
		else
			this->ev_gen->turn_off_blocking_timers(Blocking_timer_type::Jumping);

	if (my_package->give_me_your_event_type() == Event_type::ATTACK)
		if (((ATTACK_EventPackage *)my_package)->give_me_your_event_type() == Event_type::ATTACK)
			this->ev_gen->turn_off_blocking_timers(Blocking_timer_type::Attacking);

	//else if (my_package->give_me_your_direction() == Direction_type::Jump_Left || my_package->give_me_your_direction() == Direction_type::Jump_Right || my_package->give_me_your_direction() == Direction_type::Jump_Straight)
	//	this->ev_gen->active_blocking_timers(Blocking_timer_type::Jumping);


}
void LogicFSM::send_action() {
	//tengo que mandar una action(MOVE/ATTACK) LOCAL si soy servidor  (esta todo guardado en fsm->get_ev_pack())
	EventPackage* info_to_be_send = get_fsm_ev_pack();
	com->sendMessage(pack_factory.event_package_2_package(info_to_be_send)); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
	std::cout << "Se envio un MOVE" << std::endl;
}

void LogicFSM::execute_receive_action_request_send_action_and_send_ack() {

	execute_action();
	send_action();
}

void LogicFSM::check_and_send_action_request() {

	check_action();

	if (valid_action)  //The action request was valid
		send_action_request_and_set_ack_time_out();
}

void LogicFSM::execute_receive_action_and_send_ack() {

	check_action();
	if (valid_action) {
		execute_extern_action();
		received_ack_routine();
		send_ack();
	}
}

void LogicFSM::check_action() {
	EventPackage* event_to_be_checked = get_fsm_ev_pack();
	Action_info acting_information;

	switch (event_to_be_checked->give_me_your_event_type())
	{
	case Event_type::MOVE:
	{
		MOVE_EventPackage * info_mo = static_cast<MOVE_EventPackage*>(event_to_be_checked);
		acting_information = info_mo->to_Action_info();
		break;
	}
	case Event_type::ATTACK:
	{
		ATTACK_EventPackage * info_attack = static_cast<ATTACK_EventPackage*>(event_to_be_checked);
		acting_information = info_attack->to_Action_info();
		break;
	}
	case Event_type::ACTION_REQUEST:
	{
		ACTION_REQUEST_EventPackage * info_actrequest = static_cast<ACTION_REQUEST_EventPackage*>(event_to_be_checked);
		acting_information = info_actrequest->to_Action_info();
		break;
	}
	case Event_type::ENEMY_ACTION:
	{
		ENEMY_ACTION_EventPackage * info_enemyact = static_cast<ENEMY_ACTION_EventPackage*>(event_to_be_checked);
		acting_information = info_enemyact->to_Action_info();
		break;
	}
	}

	if (valid_action = scenario->is_the_action_possible(&acting_information, false))  //mando a analizar el EventPackage 
		
		//If it´s an event that should be executed ASAP, is set as an fsm eventpackage
		if (!scenario->appended_event && scenario->saved_events->empty())
		{
			set_fsm_ev_pack(ev_pack_factory.create_event_package(&acting_information));
			std::cout << "Se metio evento en la FSM" << std::endl;
		}
		
	//If it´s an event that was fetched during another process, it´s saved in a queue to be fetched and excuted later
		else if(scenario->saved_events->empty())
		{
			scenario->saved_events->push(ev_pack_factory.create_event_package(&acting_information));
			std::cout << "Se guardo evento en cola para ejecutar más tarde" << std::endl;
		}
		else
			std::cout << "No se guardo nada" << std::endl;


}

void LogicFSM::check_game_state() {
	scenario->check_current_game_situation();
}

void LogicFSM::send_action_and_set_ack_time_out() {
	//tengo que mandar una action(MOVE/ATTACK) LOCAL si soy servidor  (esta todo guardado en fsm->get_ev_pack())
	EventPackage* info_to_be_send = get_fsm_ev_pack();
	com->sendMessage(pack_factory.event_package_2_package(info_to_be_send)); //el event_package ya se forma en la fsm, se lo transforma y se lo manda

	set_ack_time_out();
}

void LogicFSM::execute_action_and_send_ack() {
	execute_action();
	send_ack();
}

void LogicFSM::send_action_request_and_set_ack_time_out() {
	EventPackage* info_to_be_send = get_fsm_ev_pack(); //EA when playing

	com->sendMessage(pack_factory.event_package_2_package(info_to_be_send)); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
	set_ack_time_out();
}

void LogicFSM::receive_name_and_send_ack() {
	user_data->my_network_data.tell_me_his_name(((NAME_IS_EventPackage *)get_fsm_ev_pack())->give_me_your_name());
	send_ack();
}

void LogicFSM::send_next_map() {

}

void LogicFSM::send_we_won() {
	com->sendMessage(pack_factory.event_package_2_package(new WE_WON_EventPackage())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
}

// Action routine for the client when it´s received an WE_WON package from the server
void LogicFSM::analyze_we_won() {

	EventPackage* event_to_be_checked = get_fsm_ev_pack();

	if (!scenario->did_we_win())
	{
		ev_gen->empty_all_queues();
		error_ocurred = true; //so the program won´t ask the user if he wants to play again
		ev_gen->append_new_event(new ERROR_EventPackage(true), (int)LogicEventGenerator::LogicQueues::soft); //load ERROR 
	}

	if (!error_ocurred)
	{
		ask_user_being_client_and_send_decition(); //By an Allegro interface
		error_ocurred = false;
	}
}

// Action routine for the client when it´s received an GAME_OVER package from the server
void LogicFSM::analyze_we_lost() {

	EventPackage* event_to_be_checked = get_fsm_ev_pack();

	if (!scenario->did_we_lose()) //mando a analizar el EventPackage sea local 
	{
		ev_gen->empty_all_queues();
		error_ocurred = true; //so the program doesn t ask the user if he wants to play again
		ev_gen->append_new_event(new ERROR_EventPackage(true), (int)LogicEventGenerator::LogicQueues::soft); //load ERROR 
	}

	if (!error_ocurred)
	{
		ask_user_being_client_and_send_decition(); //By an Allegro interface
		error_ocurred = false;
	}

}

void LogicFSM::ask_the_user_if_wants_to_play_again() {

	/*
	if(ALLEGRO INTERFACE)
	{
	fsm->want_to_play_again = true;
	}
	else
	fsm->want_to_play_again = false;

	*/
}

void LogicFSM::ask_user_being_client_and_send_decition() {

	ask_the_user_if_wants_to_play_again(); //By an Allegro interface

	if (want_to_play_again)
		send_play_again();
	else
		com->sendMessage(pack_factory.event_package_2_package(new GAME_OVER_EventPackage())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
	
	want_to_play_again = false;

}

void LogicFSM::ask_user_being_server_and_send_decition() {

	ask_the_user_if_wants_to_play_again(); //By an Allegro interface

	if (want_to_play_again)
		ev_gen->append_new_event(new PLAY_AGAIN_EventPackage(), (int)LogicEventGenerator::LogicQueues::soft);
	else
		ev_gen->append_new_event(new GAME_OVER_EventPackage(), (int)LogicEventGenerator::LogicQueues::soft);

	want_to_play_again = false;

}
void LogicFSM::tell_user_send_ack_and_finish_game() {

	/*
	ALLEGRO INTERFACE TO TELL THE USER THE OTHER COMPUTER DOESN´T WANT TO PLAY AGAIN
	*/
	send_ack();
	finish_game();
}

void LogicFSM::send_we_lost() { //el servidor le avisa a client que se perdió
	com->sendMessage((new PackageFactory())->event_package_2_package(new GAME_OVER_EventPackage())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
}
void LogicFSM::send_game_over() {
	com->sendMessage((new PackageFactory())->event_package_2_package(new GAME_OVER_EventPackage())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
}

void LogicFSM::send_play_again() {
	//tengo que mandar paquete PLAY_AGAIN!
	com->sendMessage(pack_factory.event_package_2_package(new PLAY_AGAIN_EventPackage())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
}

void LogicFSM::load_and_send_enemy_action() {
	load_enemy_action();
	send_enemy_action();
}

void LogicFSM::reset_game() {

	scenario->maps.clear();

	string new_map = "FEPEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEPEEEEEEEFFEEFFFFFFFFFFEEFFEEPEEEEEEEEPEEFFFFFFEEEEEEFFFFFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFETEEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	scenario->actual_map = -1;
	scenario->load_new_map(user_data->my_network_data.is_client(), new_map.c_str(), 18);
	
	//send RESET
	if (get_fsm_ev_pack()->is_this_a_local_action())
		com->sendMessage(pack_factory.event_package_2_package(get_fsm_ev_pack())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda

}

void LogicFSM::send_name_is() {
	NAME_IS_EventPackage * info_to_be_send = new NAME_IS_EventPackage(true, (uchar)((user_data->my_network_data.give_me_my_name()).size()), (user_data->my_network_data.give_me_my_name()).c_str());
	com->sendMessage(pack_factory.event_package_2_package(info_to_be_send)); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
	set_ack_time_out();
}


//se recibe un envio un quit por allegro, se manda el paquete QUIT por networking, paso a esperar el ACK
void LogicFSM::send_quit() {
	com->sendMessage(pack_factory.event_package_2_package(new LOCAL_QUIT_EventPackage())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
	set_ack_time_out();
}

//se devuelve un ACK con ID 0 para la otra compu, se sale
void LogicFSM::send_ack_and_quit() {

	//Interfaz del usuario avisando la situación
	send_ack();
	finish_game();
}

void LogicFSM::analayze_error()
{
	if (((ERROR_EventPackage *)get_fsm_ev_pack())->is_this_a_local_error())
		send_error_and_finish_game();
	else
		finish_game();
}

//Se sale del programa sin avisar, rutina de acción del evento ERROR1
void LogicFSM::finish_game() {

	scenario->finish_game();

}

void LogicFSM::received_ack_routine() {

	std::cout << "Se ejecuto acción" << std::endl;

	execute_local_action();
	check_game_state();
	//active_blocking_timers(get_fsm_ev_pack());


	//allegro_container->dequeu_time_out_timer();		

	//if (allegro_container->no_time_outs())		//me fijo si ya no toy esperando ningun ack mas
	//	fsm->waiting_for_ack = false;
}

void LogicFSM::check_sum_and_send_ack() {

}

void LogicFSM::send_error_and_finish_game() {
	com->sendMessage(pack_factory.event_package_2_package(new ERROR_EventPackage(true))); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
}

void LogicFSM::execute_and_send_enemy_action() {
	execute_action();
	send_enemy_action();
	set_ack_time_out();
	check_game_state();
}

void LogicFSM::save_enemy_action_and_send_it() {

	save_enemy_action();
	send_enemy_action();
}
void LogicFSM::execute_saved_enemy_actions() {

	while (scenario->assistant_queue->size() >= 1) //Execute all the pending Enemy actions beacuse the game starts
	{
		bool should_die = false;
		scenario->execute_action(&(scenario->assistant_queue)->front(), should_die);
		scenario->assistant_queue->pop();
	}
}

void LogicFSM::execute_local_action() {

	valid_local_action = !error_ocurred;
	execute_action();
}

void LogicFSM::execute_extern_action() {

	valid_extern_action = !error_ocurred;
	execute_action();
}

void LogicFSM::save_enemy_action() {
	//I´m the server, EA generated before send it during initialization
	Action_info my_enemy_action_struct = scenario->give_me_my_enemy_action(true); 

	if (!my_enemy_action_struct.finished_loading)
	{
		scenario->append_new_auxilar_event(my_enemy_action_struct);  //cola de la struct y no EVPs
		ev_gen->append_new_event(new ENEMY_ACTION_EventPackage(&my_enemy_action_struct), (int)EventGenerator::LogicQueues::soft); //has to be sent to the client
	}
}

void LogicFSM::print_curr_state()
{
}

void LogicFSM::send_enemy_action() {

	//If Scene::give_me_my_enemy_action() returns NULL, it means that all the local EA with the initial distributions where already sent to the client

	com->sendMessage(pack_factory.event_package_2_package(get_fsm_ev_pack())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
}

void LogicFSM::send_game_start() {
	//tengo que mandar paquete GAME_START!
	scenario->initializing = false; //Initialization has ended, not more Enemy Actions to be loaded
	com->sendMessage(pack_factory.event_package_2_package(new GAME_START_EventPackage())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda

	//scene get´s noticed that the game has started, has to start executing actions
	scenario->initializing = false; // ya se hace desde main

}

void LogicFSM::ask_for_name() {
	NAME_EventPackage* info_to_be_send = new NAME_EventPackage();
	com->sendMessage((new PackageFactory())->event_package_2_package(info_to_be_send)); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
}
void LogicFSM::check_map_and_save_send_ack() {

	EventPackage* event_to_be_checked = get_fsm_ev_pack();
	MAP_IS_EventPackage*map_to_be_checked = (MAP_IS_EventPackage*)event_to_be_checked;

	if (!scenario->is_the_map_okay(map_to_be_checked->give_me_the_map(), map_to_be_checked->give_me_the_checksum()))//I must check it first
	{
		ev_gen->empty_all_queues();
		ev_gen->append_new_event(new ERROR_EventPackage(true), (int)LogicEventGenerator::LogicQueues::soft); //load ERROR if the map was corrupted in the trasmition
	}
	else
	{
		scenario->load_new_map(user_data->my_network_data.is_client(), map_to_be_checked->give_me_the_map(), map_to_be_checked->give_me_the_checksum()); //If the map is okay, the program proceeds to load it
		error_ocurred = false;
	}

	if (!error_ocurred) //the map is valid, I should send an ACK
		send_ack();
}

//solo pasará si soy server
void LogicFSM::send_map_is() {
	//i´m server, load the map from the txt
	scenario->load_new_map(user_data->my_network_data.is_client());

	MAP_IS_EventPackage* info_to_be_send = new MAP_IS_EventPackage(true, scenario->maps.at(scenario->actual_map)->give_me_the_original_map(), scenario->maps.at(this->scenario->actual_map)->give_me_the_checksum());
	com->sendMessage(pack_factory.event_package_2_package(info_to_be_send)); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
	set_ack_time_out();
}
void LogicFSM::load_enemy_action_and_send_ack() {

	check_action();

	if (error_ocurred)
		valid_extern_action = false;
	else
		valid_extern_action = true;

	
	load_enemy_action();
}

void LogicFSM::load_enemy_action() {
	//I´m the client, an EA arrived during initialization by networking, I must save it to run it later
	if (error_ocurred)
		execute_extern_action();
	else
	{
		ENEMY_ACTION_EventPackage * info_EA = static_cast<ENEMY_ACTION_EventPackage*>(get_fsm_ev_pack());
		scenario->append_new_auxilar_event(info_EA->to_Action_info());
		send_ack();
	}
}

void LogicFSM::load_action_and_send_it_back() {
	check_action();
	EventPackage* info_to_be_send = NULL;
	if (valid_action) {
		execute_extern_action();

		//si soy servidor, tengo que convertir un AR del cliente en un MOVE/ATTACK  (esta todo guardado en fsm->get_ev_pack())
		EventPackage * my_movement = get_fsm_ev_pack();   //AR externo que es como llega a la fsm

		if (((ACTION_REQUEST_EventPackage *)my_movement)->give_me_the_action() == Action_type::Move)
			info_to_be_send = new MOVE_EventPackage(scenario->give_the_other_player(), ((ACTION_REQUEST_EventPackage *)my_movement)->give_me_your_destination_row(), ((ACTION_REQUEST_EventPackage *)my_movement)->give_me_your_destination_column());
		else
			info_to_be_send = new ATTACK_EventPackage(scenario->give_the_other_player(), ((ACTION_REQUEST_EventPackage *)my_movement)->give_me_your_destination_row(), ((ACTION_REQUEST_EventPackage *)my_movement)->give_me_your_destination_column());

		com->sendMessage((new PackageFactory())->event_package_2_package(info_to_be_send)); //el event_package ya se forma en la fsm, se lo transforma y se lo manda

		set_ack_time_out();
		check_game_state();
	}
}

void LogicFSM::start_game_and_send_ack() {

	scenario->initializing = false; // ya se hace desde main

	execute_saved_enemy_actions();
	send_ack();
}
void LogicFSM::set_ack_time_out() {
	//if (!(fsm->waiting_for_ack)){
	//	fsm->waiting_for_ack = true;
	//}
	//allegro_container->append_time_out_timer();	//agrego el nuevo timer
	//allegro_container->start_front_timer();		//lo inicio
}
void LogicFSM::send_ack() {
	com->sendMessage(pack_factory.event_package_2_package(new ACK_EventPackage())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda
}


void LogicFSM::execute_action() {

	if (valid_action) {		//if it´s valid, it should be executed
		Action_info action = get_fsm_ev_pack()->to_Action_info();
		if (action.action == Action_type::Move)
			scenario->load_action_on_character(action);
		else if (action.action == Action_type::Attack)
			scenario->load_action_on_projectile(action);
	}
}

