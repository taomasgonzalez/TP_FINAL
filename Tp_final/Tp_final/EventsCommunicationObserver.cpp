#include "EventsCommunicationObserver.h"



EventsCommunicationObserver::EventsCommunicationObserver(EventGenerator * event_gen, Communication * com)
{
	this->event_gen = event_gen;
	this->com = com;
}


EventsCommunicationObserver::~EventsCommunicationObserver()
{
}

void EventsCommunicationObserver::update() {
	if (event_gen->get_should_check_for_new_messages()){
		//Package * new_pack = com->receiveMessage();
		//if(new_pack != NULL)
		//	event_gen->append_new_net_event(package_2_event_package(new_pack));
	}
}