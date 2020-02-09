#include "LogicClientFSM.h"


void reset_game_r_c(void* data);


void reset_game_r_c(void* data)
{
	LogicClientFSM * fsm = (LogicClientFSM*)data;
	fsm->reset_game();
}


LogicClientFSM::LogicClientFSM(Userdata * data, LogicEventGenerator *event_gen, Scene* scene, Communication* com) : LogicFSM(data, event_gen, scene, com) {

	Initial_state = new std::vector<edge_t>();
	Naming_me_state = new std::vector<edge_t>();
	Naming_him_state = new std::vector<edge_t>();
	Waiting_for_map_state = new std::vector<edge_t>();
	Waiting_for_enemy_actions_state = new std::vector<edge_t>();
	Playing_state = new std::vector<edge_t>();
	Waiting_for_movement_state = new std::vector<edge_t>();
	Waiting_if_the_server_wants_to_play_again = new std::vector<edge_t>();
	Waiting_for_ACK_quit_state = new std::vector<edge_t>();

	Initial_state->push_back({ Event_type::NAME, this->Naming_me_state,  send_name_is_r });
	Initial_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r });//se recibe un envio un quit local, paso a esperar el ACK
	Initial_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });		//se recibe un quit por networking,
	Initial_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Initial_state->push_back({ Event_type::RESET, this->Playing_state, reset_game_r_c });
	Initial_state->push_back({ Event_type::END_OF_TABLE, this->Initial_state, do_nothing_r });

	Naming_me_state->push_back({ Event_type::ACK, this->Naming_him_state, ask_for_name_r }); //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
	Naming_me_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Naming_me_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });				//se recibe un quit por networking,
	Naming_me_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Naming_me_state->push_back({ Event_type::RESET, this->Playing_state, reset_game_r_c });
	Naming_me_state->push_back({ Event_type::END_OF_TABLE, this->Naming_me_state, do_nothing_r });

	Naming_him_state->push_back({ Event_type::NAME_IS, this->Waiting_for_map_state, receive_name_and_send_ack_r });  //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
	Naming_him_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Naming_him_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });   //se recibe un quit por networking,
	Naming_him_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Naming_him_state->push_back({ Event_type::RESET, this->Playing_state, reset_game_r_c });
	Naming_him_state->push_back({ Event_type::END_OF_TABLE, this->Naming_him_state, do_nothing_r });

	Waiting_for_map_state->push_back({ Event_type::MAP_IS, this->Waiting_for_enemy_actions_state, check_map_and_save_send_ack_r });
	Waiting_for_map_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r });  //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_map_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });  //se recibe un quit por networking,
	Waiting_for_map_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_for_map_state->push_back({ Event_type::RESET, this->Playing_state, reset_game_r_c });
	Waiting_for_map_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_map_state, do_nothing_r });

	Waiting_for_enemy_actions_state->push_back({ Event_type::ENEMY_ACTION, this->Waiting_for_enemy_actions_state, load_enemy_action_and_send_ack_r });
	Waiting_for_enemy_actions_state->push_back({ Event_type::GAME_START, this->Playing_state, start_game_and_send_ack_r });
	Waiting_for_enemy_actions_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r });
	Waiting_for_enemy_actions_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });
	Waiting_for_enemy_actions_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_for_enemy_actions_state->push_back({ Event_type::RESET, this->Playing_state, reset_game_r_c });
	Waiting_for_enemy_actions_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_enemy_actions_state, do_nothing_r });

	Playing_state->push_back({ Event_type::MOVE, this->Playing_state, execute_receive_action_and_send_ack_r }); //extern MOVE that arrives through networking , has to be checked
	Playing_state->push_back({ Event_type::ENEMY_ACTION, this->Playing_state, execute_receive_action_and_send_ack_r });
	Playing_state->push_back({ Event_type::ATTACK, this->Playing_state, execute_receive_action_and_send_ack_r });  //extern ATTACK that arrives through networking , has to be checked
	Playing_state->push_back({ Event_type::ACTION_REQUEST, this->Playing_state, check_and_send_action_request_r });	//Action request generate by allegro, has to be send to the server
	Playing_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r });		//se recibe un envio un quit local, paso a esperar el ACK
	Playing_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });	//se recibe un quit por networking,
	Playing_state->push_back({ Event_type::WE_WON, this->Waiting_if_the_server_wants_to_play_again, analyze_we_won_r });	// WE_WON from the server, must be analyzed
	Playing_state->push_back({ Event_type::GAME_OVER, this->Waiting_if_the_server_wants_to_play_again, analyze_we_lost_r });	// GAME_OVER from the server, must be analyzed
	Playing_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Playing_state->push_back({ Event_type::RESET, this->Playing_state, reset_game_r_c });
	Playing_state->push_back({ Event_type::END_OF_TABLE, this->Playing_state, do_nothing_r });

	Waiting_for_movement_state->push_back({ Event_type::MOVE, this->Playing_state, execute_receive_action_and_send_ack_r }); //extern MOVE that arrives through networking , has to be checked
	Waiting_for_movement_state->push_back({ Event_type::ATTACK, this->Playing_state, execute_receive_action_and_send_ack_r });  //extern ATTACK that arrives through networking , has to be checked
	Waiting_for_movement_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_for_movement_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_movement_state, send_quit_r });		//se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_movement_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });	//se recibe un quit por networking,
	Waiting_for_movement_state->push_back({ Event_type::RESET, this->Playing_state, reset_game_r_c });
	Waiting_for_movement_state->push_back({ Event_type::END_OF_TABLE, this->Playing_state, do_nothing_r });

	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::ACK, NULL, finish_game_r });	//ack of my game over from the server
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::MAP_IS, this->Waiting_for_enemy_actions_state, check_map_and_save_send_ack_r });	//Client wants to play again, server too
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::GAME_OVER, NULL, tell_user_send_ack_and_finish_game_r });	//Client wants to play again, server doesn´t 
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r });	//se recibe un envio un quit local, paso a esperar el ACK
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });		//se recibe un quit por networking,
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::RESET, this->Playing_state, reset_game_r_c });
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::END_OF_TABLE, this->Waiting_if_the_server_wants_to_play_again, do_nothing_r });


	Waiting_for_ACK_quit_state->push_back({ Event_type::ACK, NULL, finish_game_r });
	Waiting_for_ACK_quit_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_for_ACK_quit_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r });	//se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_ACK_quit_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });				//se recibe un quit por networking,
	Waiting_for_ACK_quit_state->push_back({ Event_type::RESET, this->Playing_state, reset_game_r_c });
	Waiting_for_ACK_quit_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_ACK_quit_state, do_nothing_r });

	if (!data->my_network_data.handshake)
	{
		this->actual_state = this->Playing_state;
		this->start_playing(); //so we start fetching allegro events in playing mood
	}
	else
		this->actual_state = this->Initial_state;
}

LogicClientFSM::~LogicClientFSM()
{
	delete Initial_state;

	delete Naming_me_state;
	delete Naming_him_state;

	delete Waiting_for_map_state;
	delete Waiting_for_enemy_actions_state;

	delete Playing_state;

	delete Waiting_for_ACK_quit_state;
	delete Waiting_if_the_server_wants_to_play_again;
}

void LogicClientFSM::print_curr_state()
{
	if (Initial_state == actual_state)
		cout << "Initial_state" << endl;
	else if (Naming_me_state == actual_state)
		cout << "Naming_me_state" << endl;
	else if (Naming_him_state == actual_state)
		cout << "Naming_him_state" << endl;
	else if (Waiting_for_map_state == actual_state)
		cout << "Waiting_for_map_state" << endl;
	else if (Waiting_for_enemy_actions_state == actual_state)
		cout << "Waiting_for_enemy_actions_state" << endl;
	else if (Playing_state == actual_state)
		cout << "Playing_state" << endl;
	else if (Waiting_if_the_server_wants_to_play_again == actual_state)
		cout << "Waiting_if_the_server_wants_to_play_again" << endl;
	else if (Waiting_for_ACK_quit_state == actual_state)
		cout << "Waiting_for_ACK_quit_state" << endl;
}

void LogicClientFSM::run_fsm(EventPackage * ev_pack) {
	LogicFSM::run_fsm(ev_pack);
	scenario->control_enemies();
}



void LogicClientFSM::reset_game() {

	scenario->maps.clear();
	ev_gen->flush_all_queues();

	while (!scenario->saved_events->empty())
		scenario->saved_events->pop();



	//mapa para caida libre
	//string new_map = "FEEEEENTEEEEEEEFFEFFFFFFFFFFFFEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEEEEFFFFFFEEEEEEFFFFFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEEEEFFFFFFFFFFFFFFFFF";

	//mapa para salto corto y largo
	//string new_map = "FEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEEEEFFFFFFEEEEEEFFFFFFEFFFFFFFFFFFFEFFEEFFFFFFFFFFEEFFETEEEEEEEEENEEFFFFFFFFFFFFFFFFF";


	//mapa sin enemigos
	//string new_map = "FEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEEEEFFFFFFEEEEEEFFFFFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFETEEEEEEEEENEEFFFFFFFFFFFFFFFFF";

	//mapa con un purple
	string new_map = "FEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEPEEFFFFFFEEEEEEFFFFFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFETEEEEEEEEENEEFFFFFFFFFFFFFFFFF";


	scenario->actual_map = -1;
	scenario->load_new_map(user_data->my_network_data.is_client(), (const unsigned char *)new_map.c_str(), 18);

	saved_EventPackages.clear();
	actual_state = Playing_state;
	//send RESET
	if (get_fsm_ev_pack()->is_this_a_local_action())
		com->sendMessage(pack_factory.event_package_2_package(get_fsm_ev_pack())); //el event_package ya se forma en la fsm, se lo transforma y se lo manda

}

