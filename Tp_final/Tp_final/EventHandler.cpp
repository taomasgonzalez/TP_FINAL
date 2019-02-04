#include "EventHandler.h"


EventHandler::EventHandler(Allegro * al, Userdata * data) :
 EventGenerator(al, data), FSM(data)
{
}


EventHandler::~EventHandler()
{
}

void EventHandler::handle_event() {

	EventPackage * ev_pack = fetch_event();
	if (ev_pack->give_me_your_event_type() != Event_type::NO_EVENT)
		run_fsm(ev_pack);

	this->my_user_data->my_network_data.set_should_check_for_new_messages(true); //cada vez que entro a correr la FSM chequeo los mensajes
	this->my_fsm->notify_obs();
	this->my_user_data->my_network_data.set_should_check_for_new_messages(false);
}

