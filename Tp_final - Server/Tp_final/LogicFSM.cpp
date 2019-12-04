#include "LogicFSM.h"

LogicFSM::LogicFSM(Userdata* data):FSM() {
	user_data = data;
}
LogicFSM::~LogicFSM() {

}


void LogicFSM::run_fsm(EventPackage * ev_pack) {

	FSM::run_fsm(ev_pack);

	user_data->my_network_data.set_should_check_for_new_messages(true); //cada vez que entro a correr la FSM chequeo los mensajes
	notify_obs();
	user_data->my_network_data.set_should_check_for_new_messages(false);
}