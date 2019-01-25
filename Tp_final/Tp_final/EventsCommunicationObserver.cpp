#include "EventsCommunicationObserver.h"



EventsCommunicationObserver::EventsCommunicationObserver(EventGenerator * event_gen, Communication * com, Userdata * data, Scene * scenario)
{
	this->event_gen = event_gen;
	this->com = com;
	this->my_user_data = data;
	this->my_scenario = scenario;

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

			if (this->my_scenario->is_the_action_possible(new_pack)) //chequeo para paquetes de networking
				event_gen->append_new_net_event(PackageFactory::package_2_event_package(new_pack));
			else
				event_gen->append_new_net_event(PackageFactory::package_2_event_package(new ERROR_package)); //no es un jugada válida, se carga error en vez de la jugada recibida

		}
	}
}