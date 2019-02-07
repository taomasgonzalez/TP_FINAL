#include "LogicServerFSM.h"
#include "LogicFSMRoutines.h"

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

