#include "CommunicationEventsObserver.h"
/*
Observer encargado de:
recibir los paquetes por networking
analizarlos a través de scenario
enviar los EVpackages a la cola de net_event

*/


CommunicationEventsObserver::CommunicationEventsObserver(LogicEventGenerator * event_gen, Communication * com, Userdata* data)
{
	this->event_gen = event_gen;
	this->com = com;
	this->my_user_data = data;

}


CommunicationEventsObserver::~CommunicationEventsObserver()
{
}

//Se encarga de recibir los paquetes de networking, chequearlos y mandarlos a la cola
void CommunicationEventsObserver::update() {
	if (my_user_data->my_network_data.get_should_check_for_new_messages())
	{
		Package * new_pack = com->receiveMessage();


		if (new_pack != NULL) //me un mensaje
		{
			EventPackage * new_event_package = (new PackageFactory())->package_2_event_package(new_pack); //convierto el paquete a EventPackage
			event_gen->append_new_event(new_event_package, (int) (LogicEventGenerator::LogicQueues::net)); //lo meto en la cola
		}
		else
		{
			//std::cout << "No se recibio ningún mensaje"  << std::endl;
		}
	}
}