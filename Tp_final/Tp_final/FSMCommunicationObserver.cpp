#include "FSMCommunicationObserver.h"



FSMCommunicationObserver::FSMCommunicationObserver(Fsm * fsm, Communication* com)
{
	this->fsm = fsm;
	this->com = com;
}


FSMCommunicationObserver::~FSMCommunicationObserver()
{
	
}
void FSMCommunicationObserver::update() {
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

	}
	if (fsm->s_game_start) {
		//tengo que mandar paquete GAME_START!

	}
}