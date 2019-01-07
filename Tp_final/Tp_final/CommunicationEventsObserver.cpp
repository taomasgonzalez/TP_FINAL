#include "CommunicationEventsObserver.h"

CommunicationEventsObserver::CommunicationEventsObserver(EventGenerator * event_gen, Communication * com)
{
	this->event_gen = event_gen;
	this->network_com = com;
}


CommunicationEventsObserver::~CommunicationEventsObserver()
{
}

void CommunicationEventsObserver::update() {
	if (network_com->has_new_info()) {
		Package *pack = network_com->get_received_package();
		EventPackage *new_ev_pack = new EventPackage();

		switch (pack->get_package_header()) {
			//filtrado de mensaje para que llegue el nuevo evento apropiado al event generator, poniendolo en la cola de eventos
			
		}
		event_gen->net_queue->push(new_ev_pack);
	}
}