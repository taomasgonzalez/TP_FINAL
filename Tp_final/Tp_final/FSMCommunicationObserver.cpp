#include "FSMCommunicationObserver.h"


FSMCommunicationObserver::FSMCommunicationObserver(Fsm * fsm, Communication* com, Scene* scenario)
{
	this->fsm = fsm;
	this->com = com;
	this->scenario = scenario;
}


FSMCommunicationObserver::~FSMCommunicationObserver()
{
	
}
void FSMCommunicationObserver::update() {

	PackageInfo my_package_info;

	//NAME
	if (fsm->ask_name) {
		//tengo que mandar paquete NAME con mi nombre.

	}

	//QUIT
	if (fsm->s_quit) {
		//tengo que mandar paquete QUIT

	}

	if (fsm->s_ack) {
		//tengo qeu mandar paquete ACK

	}

	if (fsm->s_name_is) {
		//tengo qeu mandar paquete NAME_IS
	}

	if (fsm->s_error) {
		//tengo que mandar paquete ERROR
	}

	if (fsm->s_map_is) {
		//tengo qeu mandar paquete MAP_IS!
		//package_info.map_coords = scenario->get_map_coords();
		//Package * new_pack = creeate_package(package_info);
		//com->sendMessage(new_pack);

	}
	if (fsm->s_game_start) {
		//tengo que mandar paquete GAME_START!

	}

	if (fsm->s_action) {
		//tengo que mandar una action !! (esta todo guardado en fsm->get_ev_pack())

	}
	if (fsm->s_action_request) {
		//tengo que andar un action request!! (esta todo guardado en fsm->get_ev_pack())

	}

	if (fsm->receive_name) {
		//tengo que guardar el nombre del wachin.

	}


}

