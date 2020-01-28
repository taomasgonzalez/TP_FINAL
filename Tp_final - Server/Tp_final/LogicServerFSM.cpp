#include "LogicServerFSM.h"


LogicServerFSM::LogicServerFSM(Userdata * data, LogicEventGenerator *event_gen, Scene* scene, Communication* com) : LogicFSM(data, event_gen, scene, com)
{
	Initial_state = new std::vector<edge_t>();
	Naming_him_state = new std::vector<edge_t>();
	Naming_me_state = new std::vector<edge_t>();
	Waiting_for_ACK_name_state = new std::vector<edge_t>();
	Waiting_for_ACK_quit_state = new std::vector<edge_t>();
	Waiting_for_ACK_map_state = new std::vector<edge_t>();
	Waiting_for_ACK_enemy_actions_state = new std::vector<edge_t>();
	Waiting_for_ACK_playing_state = new std::vector<edge_t>();
	Waiting_for_ACK_game_start_state = new std::vector<edge_t>();
	Playing_state = new std::vector<edge_t>();
	Waiting_if_the_client_wants_to_play_again = new std::vector<edge_t>();
	Waiting_if_the_user_wants_to_play_again = new std::vector<edge_t>();

	//Initial_state
	Initial_state->push_back({ Event_type::START_COMMUNICATION, this->Naming_him_state, ask_for_name_r });
	Initial_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Initial_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });  //se recibe un quit por networking,
	Initial_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r }); 
	Initial_state->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Initial_state->push_back({ Event_type::END_OF_TABLE, this->Initial_state, do_nothing_r });

	//Naming_him_state
	Naming_him_state->push_back({ Event_type::NAME_IS, this->Naming_me_state, receive_name_and_send_ack_r });
	Naming_him_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Naming_him_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r }); //se recibe un quit por networking,
	Naming_him_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Naming_him_state->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Naming_him_state->push_back({ Event_type::END_OF_TABLE, this->Naming_him_state, do_nothing_r });

	//Naming_me_state
	Naming_me_state->push_back({ Event_type::NAME, this->Waiting_for_ACK_name_state, send_name_is_r }); //
	Naming_me_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Naming_me_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r }); //se recibe un quit por networking,
	Naming_me_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Naming_me_state->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Naming_me_state->push_back({ Event_type::END_OF_TABLE, this->Naming_me_state, do_nothing_r });

	//Waiting_for_ACK_name_state
	Waiting_for_ACK_name_state->push_back({ Event_type::ACK, this->Waiting_for_ACK_map_state, send_map_is_r });
	Waiting_for_ACK_name_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_ACK_name_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r });					//se recibe un quit por networking,
	Waiting_for_ACK_name_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_for_ACK_name_state->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Waiting_for_ACK_name_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_ACK_name_state, do_nothing_r });

	//Waiting_for_ACK_map_state
	Waiting_for_ACK_map_state->push_back({ Event_type::ACK, this->Waiting_for_ACK_enemy_actions_state,  save_enemy_action_r });
	Waiting_for_ACK_map_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_ACK_map_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r }); //se recibe un quit por networking,
	Waiting_for_ACK_map_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_for_ACK_map_state->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Waiting_for_ACK_map_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_ACK_map_state, do_nothing_r });

	//Waiting_for_ACK_enemy_actions_state
	Waiting_for_ACK_enemy_actions_state->push_back({ Event_type::ACK, this->Waiting_for_ACK_enemy_actions_state, save_enemy_action_r });
	Waiting_for_ACK_enemy_actions_state->push_back({ Event_type::ENEMY_ACTION, this->Waiting_for_ACK_enemy_actions_state,  send_enemy_action_r });
	Waiting_for_ACK_enemy_actions_state->push_back({ Event_type::ENEMYS_LOADED, this->Waiting_for_ACK_game_start_state, send_game_start_r });
	Waiting_for_ACK_enemy_actions_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_ACK_enemy_actions_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r }); //se recibe un quit por networking,
	Waiting_for_ACK_enemy_actions_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_for_ACK_enemy_actions_state->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Waiting_for_ACK_enemy_actions_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_ACK_enemy_actions_state, do_nothing_r });

	//Waiting_for_ACK_game_start_state
	Waiting_for_ACK_game_start_state->push_back({ Event_type::ACK, this->Playing_state, execute_saved_enemy_actions_r }); //the game begins for the server
	Waiting_for_ACK_game_start_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_ACK_game_start_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r }); //se recibe un quit por networking,
	Waiting_for_ACK_game_start_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_for_ACK_game_start_state->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Waiting_for_ACK_game_start_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_ACK_game_start_state, do_nothing_r });

	//Playing_state
	Playing_state->push_back({ Event_type::ENEMY_ACTION, this->Waiting_for_ACK_playing_state, execute_and_send_enemy_action_r }); //local ENEMY_ACTION evento software already loaded, only has to be sent
	Playing_state->push_back({ Event_type::MOVE, this->Waiting_for_ACK_playing_state, execute_action_send_it_and_set_ack_time_out_r }); //MOVE local generado desde allegro, has to be send to the client if valid
	Playing_state->push_back({ Event_type::ATTACK, this->Waiting_for_ACK_playing_state, execute_action_send_it_and_set_ack_time_out_r }); //ATTACK local generado desde allegro, has to be send to the client if valir
	Playing_state->push_back({ Event_type::ACTION_REQUEST, this->Waiting_for_ACK_playing_state, load_action_and_send_it_back_r });   //AR del cliente
	Playing_state->push_back({ Event_type::FINISHED_LEVEL, this->Waiting_for_ACK_map_state, send_map_is_r });		//evento de software que se termino el nivel
	Playing_state->push_back({ Event_type::WE_WON, this->Waiting_if_the_client_wants_to_play_again, send_we_won_r }); //we_won local generado por soft, le aviso a client que ganamos
	Playing_state->push_back({ Event_type::GAME_OVER, this->Waiting_if_the_client_wants_to_play_again, send_we_lost_r });  //game_over local generado por soft, le aviso a client que perdimos
	Playing_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Playing_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r }); //se recibe un quit por networking,
	Playing_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Playing_state->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Playing_state->push_back({ Event_type::END_OF_TABLE, this->Playing_state, do_nothing_r });

	//Waiting_for_ACK_playing_state
	Waiting_for_ACK_playing_state->push_back({ Event_type::ACK, this->Playing_state, received_ack_routine_r }); //Se recibe un ACK del clinte de un MOVE/ATTACK enviado
	Waiting_for_ACK_playing_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_ACK_playing_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r }); //se recibe un quit por networking,
	Waiting_for_ACK_playing_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_for_ACK_playing_state->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Waiting_for_ACK_playing_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_ACK_playing_state, do_nothing_r });

	//Waiting_if_the_client_wants_to_play_again
	Waiting_if_the_client_wants_to_play_again->push_back({ Event_type::PLAY_AGAIN, this->Waiting_if_the_user_wants_to_play_again, ask_user_being_server_and_send_decition_r }); //se recibe un PLAY_AGAIN del client que quiere volver a jugar
	Waiting_if_the_client_wants_to_play_again->push_back({ Event_type::GAME_OVER, NULL, tell_user_send_ack_and_finish_game_r });  //se recibe un GAME_OVER del client que no quiere volver a jugar
	//Waiting_if_the_client_wants_to_play_again->push_back({ Event_type::ACK, NULL, finish_game_r });	 //??? chequear creo que no corresponde, nunca llega un ACK							//validación del client a un paquete GAME_OVER mandado por el servidor desde ask_user_and_send_decition()
	Waiting_if_the_client_wants_to_play_again->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_if_the_client_wants_to_play_again->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r }); //se recibe un quit por networking,
	Waiting_if_the_client_wants_to_play_again->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_if_the_client_wants_to_play_again->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Waiting_if_the_client_wants_to_play_again->push_back({ Event_type::END_OF_TABLE, this->Waiting_if_the_client_wants_to_play_again, do_nothing_r });

	//Waiting_if_the_user_wants_to_play_again
	Waiting_if_the_user_wants_to_play_again->push_back({ Event_type::PLAY_AGAIN, this->Waiting_for_ACK_map_state, send_map_is_r });  //el usuario del servidor quiere volver a jugar
	Waiting_if_the_user_wants_to_play_again->push_back({ Event_type::GAME_OVER, this->Waiting_if_the_user_wants_to_play_again, send_game_over_r }); //el usuario del servidor no quiere volver a jugar
	Waiting_if_the_user_wants_to_play_again->push_back({ Event_type::ACK, NULL, finish_game_r });										//ACK del GAME_OVER del usuario del servidor
	Waiting_if_the_user_wants_to_play_again->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_if_the_user_wants_to_play_again->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r }); //se recibe un quit por networking,
	Waiting_if_the_user_wants_to_play_again->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_if_the_user_wants_to_play_again->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Waiting_if_the_user_wants_to_play_again->push_back({ Event_type::END_OF_TABLE, this->Waiting_if_the_user_wants_to_play_again, do_nothing_r });

	//Waiting_for_ACK_quit_state
	Waiting_for_ACK_quit_state->push_back({ Event_type::ACK, NULL, finish_game_r });
	Waiting_for_ACK_quit_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit_r }); //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_ACK_quit_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit_r }); //se recibe un quit por networking,
	Waiting_for_ACK_quit_state->push_back({ Event_type::ERROR1, NULL, analayze_error_r });
	Waiting_for_ACK_quit_state->push_back({ Event_type::RESET, Playing_state, reset_game_r });
	Waiting_for_ACK_quit_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_ACK_quit_state, do_nothing_r });

	if (!data->my_network_data.handshake) //hardcodeo hasta que esté listo el handshake
	{
		actual_state = Playing_state;
		this->start_playing(); //so we start fetching allegro events in playing mood
	}
	else
		actual_state = Initial_state;

	control_ev_queue = al_create_event_queue();
	control_timer = al_create_timer(3);
	al_register_event_source(control_ev_queue, al_get_timer_event_source(control_timer));
	al_start_timer(control_timer);
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


void LogicServerFSM::run_fsm(EventPackage * ev_pack) {
	static bool may_control_enemies = false;

	if (!may_control_enemies) {
		ALLEGRO_EVENT al_event;
		if (al_get_next_event(control_ev_queue, &al_event)) {
			al_stop_timer(control_timer);
			while (al_get_next_event(control_ev_queue, &al_event));
			may_control_enemies = true;
		}

	}
	
	LogicFSM::run_fsm(ev_pack);
	if(may_control_enemies)
		scenario->control_enemy_actions();
}


void LogicServerFSM::print_curr_state()
{

	if (Initial_state == actual_state)
		cout << "Initial_state" << endl;
	else if (Naming_me_state == actual_state)
		cout << "Naming_me_state" << endl;
	else if (Naming_him_state == actual_state)
		cout << "Naming_him_state" << endl;
	else if (Waiting_for_ACK_name_state == actual_state)
		cout << "Waiting_for_ACK_name_state" << endl;
	else if (Waiting_for_ACK_map_state == actual_state)
		cout << "Waiting_for_map_state" << endl;
	else if (Waiting_for_ACK_enemy_actions_state == actual_state)
		cout << "Waiting_for_ACK_enemy_actions_state" << endl;
	else if (Playing_state == actual_state)
		cout << "Playing_state" << endl;
	else if (Waiting_for_ACK_playing_state == actual_state)
		cout << "Waiting_for_ACK_playing_state" << endl;
	else if (Waiting_for_ACK_game_start_state == actual_state)
		cout << "Waiting_for_ACK_game_start_state" << endl;
	else if (Waiting_if_the_client_wants_to_play_again == actual_state)
		cout << "Waiting_if_the_client_wants_to_play_again" << endl;
	else if (Waiting_if_the_user_wants_to_play_again == actual_state)
		cout << "Waiting_if_the_user_wants_to_play_again" << endl;
	else if (Waiting_for_ACK_quit_state == actual_state)
		cout << "Waiting_for_ACK_quit_state" << endl;
}