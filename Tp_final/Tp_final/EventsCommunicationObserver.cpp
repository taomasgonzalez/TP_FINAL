#include "EventsCommunicationObserver.h"



EventsCommunicationObserver::EventsCommunicationObserver(EventGenerator * event_gen, Communication * com, Userdata * data)
{
	this->event_gen = event_gen;
	this->com = com;
	this->my_user_data = data;

}


EventsCommunicationObserver::~EventsCommunicationObserver()
{
}

void EventsCommunicationObserver::update() {
	if (this->my_user_data->my_network_data.get_should_check_for_new_messages())
	{
		Package * new_pack = com->receiveMessage();
		if (new_pack != NULL)
		{
			//aca hay que chequear el evento con funcion en scene antes de pasarlo
			event_gen->append_new_net_event(PackageFactory::package_2_event_package(new_pack));
		}
	}
}