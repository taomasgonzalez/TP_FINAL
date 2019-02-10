#include "FSMCommunicationObserver.h"


FSMCommunicationObserver::FSMCommunicationObserver(LogicFSM * fsm, Communication* com, Scene* scenario,Userdata * data)
{
	this->fsm = fsm;
	this->com = com;
	this->scenario = scenario;
	this->my_user_data = data;

}


FSMCommunicationObserver::~FSMCommunicationObserver()
{
	
}

void FSMCommunicationObserver::update() {

//    INNECESARIO, EL EVENTPACKAGE YA LLEGA CARGADO A LA FSM

	//EventPackage* my_event_info=this->fsm->get_fsm_ev_pack();
	EventPackage* info_to_be_send=NULL;

	//NAME
	if (fsm->s_name) {
		//tengo que mandar paquete NAME para preguntar nombre
		info_to_be_send = new NAME_EventPackage();

	}

	//QUIT
	if (fsm->s_quit) {
		//tengo que mandar paquete QUIT
		info_to_be_send = new LOCAL_QUIT_EventPackage();

	}

	if (fsm->s_ack) {
		//tengo qeu mandar paquete ACK
		info_to_be_send = new ACK_EventPackage();


	}

	if (fsm->s_name_is) {
		//tengo qeu mandar paquete NAME_IS
		info_to_be_send = new NAME_IS_EventPackage(true, (uchar)((my_user_data->my_network_data.give_me_my_name()).size()), my_user_data->my_network_data.give_me_my_name().c_str());

	}

	if (fsm->s_error) {
		//tengo que mandar paquete ERROR
		info_to_be_send = new ERROR_EventPackage(true);

	}

	if (fsm->s_map_is) {
		//tengo qeu mandar paquete MAP_IS! //investigar vectores y ponerlo lindo, solo pasará si soy server
		info_to_be_send = new MAP_IS_EventPackage(true,scenario->maps.at(scenario->actual_map)->give_me_the_original_map(), scenario->maps.at(this->scenario->actual_map)->give_me_the_checksum() );
		this->scenario->actual_map++;

	}
	if (fsm->s_game_start) {
		//tengo que mandar paquete GAME_START!
		info_to_be_send = new GAME_START_EventPackage();
		scenario->initializing = false; //Initialization has ended, not more Enemy Actions to be loaded

	}
	if (fsm->s_game_over) {
		//tengo que mandar paquete GAME_OVER!
		info_to_be_send = new GAME_OVER_EventPackage();
	}

	if (fsm->s_we_won) {
		//tengo que mandar paquete WE_WON!
		info_to_be_send = new WE_WON_EventPackage();
	}
	if (fsm->s_play_again) {
		//tengo que mandar paquete PLAY_AGAIN!
		info_to_be_send = new PLAY_AGAIN_EventPackage();
	}

	if (fsm->s_action) {
		//tengo que mandar una action(MOVE/ATTACK) LOCAL si soy servidor  (esta todo guardado en fsm->get_ev_pack())
		info_to_be_send =  fsm->get_fsm_ev_pack();

	}

	if (fsm->s_action_from_action_request) {
		//si soy servidor, tengo que convertir un AR del cliente en un MOVE/ATTACK  (esta todo guardado en fsm->get_ev_pack())
		EventPackage * my_movement = fsm->get_fsm_ev_pack();   //AR externo que es como llega a la fsm
		if (((ACTION_REQUEST_EventPackage *)my_movement)->give_me_the_action() == Action_type::Move)

			info_to_be_send = new MOVE_EventPackage( this->scenario->give_the_other_player(), ((ACTION_REQUEST_EventPackage *)my_movement)->give_me_your_destination_row(), ((ACTION_REQUEST_EventPackage *)my_movement)->give_me_your_destination_column());

		else
			info_to_be_send = new ATTACK_EventPackage(this->scenario->give_the_other_player(), ((ACTION_REQUEST_EventPackage *)my_movement)->give_me_your_destination_row(), ((ACTION_REQUEST_EventPackage *)my_movement)->give_me_your_destination_column());

	}

	if (fsm->s_enemy_action) {
		//If Scene::give_me_my_enemy_action() returns NULL, it means that all the local EA with the initial distributions where already sent to the client
		info_to_be_send = fsm->get_fsm_ev_pack(); //EA when playing
	}

	if (fsm->s_action_request) {
		//soy cliente, allegro lo detecta y me genera directamente un action request qeu ingresa a la FSM, por tanto queda guardado en la misma 
		info_to_be_send = fsm->get_fsm_ev_pack(); //EA when playing

	}


	if(info_to_be_send != NULL) //hay algo para mandar
		com->sendMessage(PackageFactory::event_package_2_package(info_to_be_send)); //el event_package ya se forma en la fsm, se lo transforma y se lo manda


}

