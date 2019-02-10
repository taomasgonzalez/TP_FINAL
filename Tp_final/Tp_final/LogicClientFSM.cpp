#include "LogicClientFSM.h"
#include "LogicFSMRoutines.h"

LogicClientFSM::LogicClientFSM(Userdata* data): LogicFSM(data){

	Initial_state = new std::vector<edge_t>();
	Naming_me_state = new std::vector<edge_t>();
	Naming_him_state = new std::vector<edge_t>();
	Waiting_for_map_state = new std::vector<edge_t>();
	Waiting_for_enemy_actions_state = new std::vector<edge_t>();
	Playing_state = new std::vector<edge_t>();
	Waiting_for_servers_response_state = new std::vector<edge_t>();
	Waiting_if_the_server_wants_to_play_again = new std::vector<edge_t>();
	Waiting_for_ACK_quit_state = new std::vector<edge_t>();

	Initial_state->push_back({ Event_type::NAME, this->Naming_me_state,  send_name_is });
	Initial_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit });//se recibe un envio un quit local, paso a esperar el ACK
	Initial_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit });		//se recibe un quit por networking,
	Initial_state->push_back({ Event_type::ERROR1, NULL, analayze_error });
	Initial_state->push_back({ Event_type::END_OF_TABLE, this->Initial_state, do_nothing });

	Naming_me_state->push_back({ Event_type::ACK, this->Naming_him_state, ask_for_name }); //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
	Naming_me_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }); //se recibe un envio un quit local, paso a esperar el ACK
	Naming_me_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit });				//se recibe un quit por networking,
	Naming_me_state->push_back({ Event_type::ERROR1, NULL, analayze_error });
	Naming_me_state->push_back({ Event_type::END_OF_TABLE, this->Naming_me_state, do_nothing });

	Naming_him_state->push_back({ Event_type::NAME_IS, this->Waiting_for_map_state, receive_name_and_send_ack });  //va a estar creado el worm, mando evento IAMREADY CON SU POSICION
	Naming_him_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }); //se recibe un envio un quit local, paso a esperar el ACK
	Naming_him_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit });   //se recibe un quit por networking,
	Naming_him_state->push_back({ Event_type::ERROR1, NULL, analayze_error });
	Naming_him_state->push_back({ Event_type::END_OF_TABLE, this->Naming_him_state, do_nothing });

	Waiting_for_map_state->push_back({ Event_type::MAP_IS, this->Waiting_for_enemy_actions_state, check_map_and_save_send_ack });
	Waiting_for_map_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit });  //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_map_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit });  //se recibe un quit por networking,
	Waiting_for_map_state->push_back({ Event_type::ERROR1, NULL, analayze_error });
	Waiting_for_map_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_map_state, do_nothing });

	Waiting_for_enemy_actions_state->push_back({ Event_type::ENEMY_ACTION, this->Waiting_for_enemy_actions_state, load_enemy_action_and_send_ack });
	Waiting_for_enemy_actions_state->push_back({ Event_type::GAME_START, this->Playing_state, start_game_and_send_ack });
	Waiting_for_enemy_actions_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit });
	Waiting_for_enemy_actions_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit });
	Waiting_for_enemy_actions_state->push_back({ Event_type::ERROR1, NULL, analayze_error });
	Waiting_for_enemy_actions_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_enemy_actions_state, do_nothing });

	Playing_state->push_back({ Event_type::ENEMY_ACTION, this->Playing_state, execute_receive_action_and_send_ack });
	Playing_state->push_back({ Event_type::ACTION_REQUEST, this->Waiting_for_servers_response_state, check_and_send_action_request });	//Action request generate by allegro, has to be send to the server
	Playing_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit });		//se recibe un envio un quit local, paso a esperar el ACK
	Playing_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit });	//se recibe un quit por networking,
	Playing_state->push_back({ Event_type::WE_WON, this->Waiting_if_the_server_wants_to_play_again, analyze_we_won });	// WE_WON from the server, must be analyzed
	Playing_state->push_back({ Event_type::GAME_OVER, this->Waiting_if_the_server_wants_to_play_again, analyze_we_lost });	// GAME_OVER from the server, must be analyzed
	Playing_state->push_back({ Event_type::ERROR1, NULL, analayze_error });
	Playing_state->push_back({ Event_type::END_OF_TABLE, this->Playing_state, do_nothing });

	Waiting_for_servers_response_state->push_back({ Event_type::MOVE, this->Playing_state, execute_receive_action_and_send_ack }); //extern MOVE that arrives through networking , has to be checked
	Waiting_for_servers_response_state->push_back({ Event_type::ATTACK, this->Playing_state, execute_receive_action_and_send_ack });  //extern ATTACK that arrives through networking , has to be checked
	Waiting_for_servers_response_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }); //se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_servers_response_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }); //se recibe un quit por networking,
	Waiting_for_servers_response_state->push_back({ Event_type::ERROR1, NULL, analayze_error });
	Waiting_for_servers_response_state->push_back({ Event_type::END_OF_TABLE, this->Playing_state, do_nothing });


	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::ACK, NULL, finish_game });	//ack of my game over from the server
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::MAP_IS, this->Waiting_for_enemy_actions_state, check_map_and_save_send_ack });	//Client wants to play again, server too
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::GAME_OVER, NULL, tell_user_send_ack_and_finish_game });	//Client wants to play again, server doesn´t 
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit });	//se recibe un envio un quit local, paso a esperar el ACK
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit });		//se recibe un quit por networking,
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::ERROR1, NULL, analayze_error });
	Waiting_if_the_server_wants_to_play_again->push_back({ Event_type::END_OF_TABLE, this->Waiting_if_the_server_wants_to_play_again, do_nothing });


	Waiting_for_ACK_quit_state->push_back({ Event_type::ACK, NULL, finish_game });
	Waiting_for_ACK_quit_state->push_back({ Event_type::ERROR1, NULL, analayze_error });
	Waiting_for_ACK_quit_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit });	//se recibe un envio un quit local, paso a esperar el ACK
	Waiting_for_ACK_quit_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit });				//se recibe un quit por networking,
	Waiting_for_ACK_quit_state->push_back({ Event_type::END_OF_TABLE, this->Waiting_for_ACK_quit_state, do_nothing });

	this->actual_state = this->Initial_state;

}


LogicClientFSM::~LogicClientFSM()
{
	delete Initial_state;

	delete Naming_me_state;
	delete Naming_him_state;

	delete Waiting_for_map_state;
	delete Waiting_for_enemy_actions_state;
	delete Waiting_for_servers_response_state;

	delete Playing_state;

	delete Waiting_for_ACK_quit_state;
	delete Waiting_if_the_server_wants_to_play_again;
}

