#include "FSMCommunicationObserver.h"


FSMCommunicationObserver::FSMCommunicationObserver(FSM * fsm, Communication* com, Scene* scenario)
{
	this->fsm = fsm;
	this->com = com;
	this->scenario = scenario;

}


FSMCommunicationObserver::~FSMCommunicationObserver()
{
	
}

void FSMCommunicationObserver::update() {

	EventPackage* my_event_info=this->fsm->get_fsm_ev_pack();
	PackageInfo* my_package_info;



	//NAME
	if (fsm->ask_name) {
		//tengo que mandar paquete NAME para preguntar nombre
		my_package_info = new PackageInfo(Package_type::NAME, this->scenario, this->com, my_event_info);

	}

	//QUIT
	if (fsm->s_quit) {
		//tengo que mandar paquete QUIT
		my_package_info = new PackageInfo(Package_type::QUIT, this->scenario, this->com, my_event_info);


	}

	if (fsm->s_ack) {
		//tengo qeu mandar paquete ACK
		my_package_info = new PackageInfo(Package_type::ACK, this->scenario, this->com, my_event_info);


	}

	if (fsm->s_name_is) {
		//tengo qeu mandar paquete NAME_IS
		my_package_info = new PackageInfo(Package_type::NAME_IS, this->scenario, this->com, my_event_info);

	}

	if (fsm->s_error) {
		//tengo que mandar paquete ERROR
		my_package_info = new PackageInfo (Package_type::ERROR1, this->scenario, this->com, my_event_info);

	}

	if (fsm->s_map_is) {
		//tengo qeu mandar paquete MAP_IS!
		my_package_info = new PackageInfo(Package_type::MAP_IS, this->scenario, this->com, my_event_info);

	}
	if (fsm->s_game_start) {
		//tengo que mandar paquete GAME_START!
		my_package_info = new PackageInfo(Package_type::GAME_START, this->scenario, this->com, my_event_info);

	}

	if (fsm->s_action) {
		//tengo que mandar una action !! (esta todo guardado en fsm->get_ev_pack())
		if(my_event_info->my_info->action== Action_type::Attack)
			my_package_info = new PackageInfo(Package_type::ATTACK, this->scenario, this->com, my_event_info);
		else
			my_package_info = new PackageInfo(Package_type::MOVE, this->scenario, this->com, my_event_info);

	}

	if (fsm->s_enemy_action) {
		//tengo que mandar una enemy_action !! (esta todo guardado en fsm->get_ev_pack())
		my_package_info = new PackageInfo(Package_type::ENEMY_ACTION, this->scenario, this->com, my_event_info);


	}
	if (fsm->s_action_request) {
		//tengo que andar un action request!! (esta todo guardado en fsm->get_ev_pack())
		my_package_info = new PackageInfo(Package_type::ACTION_REQUEST, this->scenario, this->com, my_event_info);


	}

	if (fsm->receive_name) {
		//tengo que guardar el nombre del wachin.


	}

	com->sendMessage(PackageFactory::event_package_2_package(my_package_info)); //add how to notify the game that an error happened within the communication


}

