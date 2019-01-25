#include "FSMCommunicationObserver.h"


FSMCommunicationObserver::FSMCommunicationObserver(FSM * fsm, Communication* com, Scene* scenario,Userdata * data)
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
	EventPackage* info_to_be_send;

	//NAME
	if (fsm->ask_name) {
		//tengo que mandar paquete NAME para preguntar nombre
		info_to_be_send = new NAME_EventPackage(true);

	}

	//QUIT
	if (fsm->s_quit) {
		//tengo que mandar paquete QUIT
		info_to_be_send = new QUIT_EventPackage(true);


	}

	if (fsm->s_ack) {
		//tengo qeu mandar paquete ACK
		info_to_be_send = new ACK_EventPackage(true);


	}

	if (fsm->s_name_is) {
		//tengo qeu mandar paquete NAME_IS
		info_to_be_send = new NAME_IS_EventPackage(true, (this->my_user_data->my_network_data.give_me_my_name()).size(),this->my_user_data->my_network_data.give_me_my_name().c_str());

	}

	if (fsm->s_error) {
		//tengo que mandar paquete ERROR
		info_to_be_send = new ERROR_EventPackage(true);

	}

	if (fsm->s_map_is) {
		//tengo qeu mandar paquete MAP_IS! //investigar vectores y ponerlo lindo, solo pasará si soy server
		info_to_be_send = new MAP_IS_EventPackage(true,this->scenario->maps.at(this->scenario->actual_map)->give_me_the_original_map(), this->scenario->maps.at(this->scenario->actual_map)->give_me_the_checksum() );


	}
	if (fsm->s_game_start) {
		//tengo que mandar paquete GAME_START!
		info_to_be_send = new GAME_START_EventPackage(true);

	}

	if (fsm->s_action) {
		//tengo que mandar una action(MOVE/ATTACK) !! (esta todo guardado en fsm->get_ev_pack())
		info_to_be_send =  fsm->get_fsm_ev_pack();

	}

	if (fsm->s_enemy_action) {
		//tengo que mandar una enemy_action !! (esta todo guardado en fsm->get_ev_pack())
		info_to_be_send = fsm->get_fsm_ev_pack();

	}
	if (fsm->s_action_request) {
		//tengo que andar un action request!! (esta todo guardado en fsm->get_ev_pack())
		info_to_be_send = new PackageInfo(Package_type::ACTION_REQUEST, this->scenario, this->com, my_event_info);


	}

	if (fsm->receive_name) {
		//tengo que guardar el nombre del wachin.


	}

	com->sendMessage(PackageFactory::event_package_2_package(info_to_be_send)); //el event_package ya se forma en la fsm, se lo transforma y se lo manda


}

