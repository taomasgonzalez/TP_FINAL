#include "LogicServerFSM.h"
#include "LogicFSMRoutines.h"

LogicServerFSM::LogicServerFSM(Userdata * data) : LogicFSM(data)
{

	Initial_state = new std::vector<edge_t>();

	Naming_him_state = new std::vector<edge_t>();
	Naming_me_state = new std::vector<edge_t>();

	Waiting_for_ACK_name_state = new std::vector<edge_t>();

	Waiting_for_map_state = new std::vector<edge_t>();
	Waiting_for_ACK_map_state = new std::vector<edge_t>();

	Waiting_for_enemy_actions_state = new std::vector<edge_t>();
	Waiting_for_ACK_enemy_actions_state = new std::vector<edge_t>();

	Waiting_for_game_start_state = new std::vector<edge_t>();
	Waiting_for_ACK_game_start_state = new std::vector<edge_t>();

	Playing_state = new std::vector<edge_t>();

	Waiting_for_ACK_quit_state = new std::vector<edge_t>();

	Waiting_for_ACK_playing_state = new std::vector<edge_t>();
	Waiting_for_servers_response_state = new std::vector<edge_t>();

	Waiting_if_the_client_wants_to_play_again = new std::vector<edge_t>();
	Waiting_if_the_server_wants_to_play_again = new std::vector<edge_t>();
	Waiting_if_the_user_wants_to_play_again = new std::vector<edge_t>();

	Initial_state->push_back({ Event_type::START_COMMUNICATION, this->Naming_him_state, ask_for_name });
	Initial_state->push_back({ Event_type::LOCAL_QUIT, this->Waiting_for_ACK_quit_state, send_quit }); //se recibe un envio un quit local, paso a esperar el ACK
	Initial_state->push_back({ Event_type::EXTERN_QUIT, NULL, send_ack_and_quit }); 
	Initial_state->push_back({ Event_type::END_OF_TABLE, this->Initial_state, do_nothing });
	expand_state(Initial_state, { Event_type::ERROR1, NULL, analayze_error });
	


	actual_state = Initial_state;

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

