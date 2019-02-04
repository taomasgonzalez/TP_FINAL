#include "EventHandler.h"


EventHandler::EventHandler(FSM * fsm, EventGenerator* ev_gen, Allegro* al, Userdata * data)
{
	this->fsm = fsm;
	this->ev_gen = ev_gen;
	my_user_data = data;
	this->al = al;
}


EventHandler::~EventHandler()
{
}

void EventHandler::handle_event() {

	EventPackage * ev_pack = ev_gen->fetch_event();
	if (ev_pack->give_me_your_event_type() != Event_type::NO_EVENT)
		fsm->run_fsm(ev_pack);

	my_user_data->my_network_data.set_should_check_for_new_messages(true); //cada vez que entro a correr la FSM chequeo los mensajes
	fsm->notify_obs();
	my_user_data->my_network_data.set_should_check_for_new_messages(false);
}

