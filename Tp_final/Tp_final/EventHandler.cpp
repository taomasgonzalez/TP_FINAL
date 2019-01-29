#include "EventHandler.h"


EventHandler::EventHandler(Allegro * al, Userdata * data) :
 EventGenerator(al, data), FSM(data)
{

}


EventHandler::~EventHandler()
{
}

void EventHandler::handle_event() {

	EventPackage * ev_pack_soft = fetch_event_soft();
	if (ev_pack_soft->give_me_your_event_type() != Event_type::NO_EVENT)
		this->run_fsm(ev_pack_soft);

	EventPackage * ev_pack_al = fetch_event_al();
	if (ev_pack_al->give_me_your_event_type() != Event_type::NO_EVENT) 
		this->run_fsm(ev_pack_al);

	EventPackage * ev_pack_net = fetch_event_net();
	if (ev_pack_net->give_me_your_event_type() != Event_type::NO_EVENT)
		this->run_fsm(ev_pack_net);


	this->my_user_data->my_network_data.set_should_check_for_new_messages(true); //cada vez que entro a correr la FSM chequeo los mensajes
	this->my_fsm->notify_obs();
	this->my_user_data->my_network_data.set_should_check_for_new_messages(false);
}

