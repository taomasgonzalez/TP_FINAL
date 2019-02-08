#include "Resources.h"


Resources::Resources() {

	this->my_scenario = new Scene;
	this->my_allegro_container = new Allegro;
	this->my_user_data = new Userdata;
	this->my_drawer = new DRAW();
};

Resources::~Resources() {  //Delete all the resources loaded

	delete my_scenario;
	delete my_allegro_container;
	delete my_user_data;
	delete my_communication;
	delete my_logic_event_handler;
	delete my_graphic_event_handler;
};


bool Resources::Intialize_all_the_resources() {

	bool healthy_initialization = true;

	healthy_initialization = my_allegro_container->Init(*my_user_data);  //se puede ver de pedirla por allegro, el tema es que no estaría iniciado todavía

	if (healthy_initialization)
	{
		my_communication = new Communication(my_user_data);  //Initialize the communication
		healthy_initialization = this->my_communication->is_the_connection_healthy();  //Checks if the communication process was successful
	}

	if (my_user_data->my_network_data.is_client()) {
		my_logic_fsm =(LogicFSM*) new LogicClientFSM(my_user_data);
		my_logic_event_handler = new EventHandler(my_logic_fsm, new LogicEventGenerator(my_allegro_container, my_user_data), my_allegro_container, my_user_data);
	}
	else {
		my_logic_fsm = (LogicFSM*) new LogicServerFSM(my_user_data);
		my_logic_event_handler = new EventHandler(my_logic_fsm, new LogicEventGenerator(my_allegro_container, my_user_data), my_allegro_container, my_user_data);
	}

	my_graphic_fsm = new GraphicGameFSM(my_user_data, my_drawer);
	my_graphic_event_handler = new EventHandler(my_graphic_fsm, new GraphicEventGenerator(my_allegro_container, my_user_data), my_allegro_container, my_user_data);

	add_all_observers();

	return healthy_initialization;
};

void Resources::add_all_observers() {

}