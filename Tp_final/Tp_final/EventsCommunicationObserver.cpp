#include "EventsCommunicationObserver.h"
/*
Observer encargado de:
recibir los paquetes por networking
analizarlos a través de scenario
enviar los EVpackages a la cola de net_event


*/


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

//Se encarga de recibir los paquetes de networking, chequearlos y mandarlos a la cola
void EventsCommunicationObserver::update() {
	if (this->my_user_data->my_network_data.get_should_check_for_new_messages())
	{
		Package * new_pack = com->receiveMessage();
		EventPackage * new_event_package = PackageFactory::package_2_event_package(new_pack); //convierto el paquete a EventPackage

		if (new_pack != NULL)
		{
			this->my_scenario->is_the_action_possible(new_event_package);//mando a analizar el EventPackage que llego por Networking
			
			if (new_event_package->is_this_a_valid_action()==true) //es una jugada válida, se carga la jugada en la cola
				event_gen->append_new_net_event(new_event_package);

			if(new_event_package->is_this_a_valid_action()==false) //no es un jugada válida, se carga error externo en vez de la jugada recibida
				event_gen->append_new_net_event(new ERROR_EventPackage(false));

		}
		else
		{
			std::cout << "No se recibio ningún mensaje"  << std::endl;
		}
	}
}