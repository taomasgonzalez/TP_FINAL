#include "EventsCommunicationObserver.h"



EventsCommunicationObserver::EventsCommunicationObserver(EventGenerator * event_gen, Communication * com)
{
}


EventsCommunicationObserver::~EventsCommunicationObserver()
{
}

void EventsCommunicationObserver::update() {
	if (event_gen->get_should_check_for_new_messages()){
		com->receiveMessage();
		event_gen->set_should_check_for_new_messages(false);
	}
}