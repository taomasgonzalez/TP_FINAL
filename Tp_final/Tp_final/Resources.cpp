#include "Resources.h"


Resources::Resources() {

	this->my_scenario = new Scene;
	this->my_drawing_manager = new Drawer;
	this->my_allegro_container = new Allegro;
	this->my_user_data = new Userdata;
};

Resources::~Resources() {  //Delete all the resources loaded

	delete this->my_scenario;
	delete this->my_drawing_manager;
	delete this->my_allegro_container;
	delete this->my_user_data;
	delete this->my_communication;

};


bool Resources::Intialize_all_the_resources() {

	bool healthy_initialization = true;

	healthy_initialization = this->my_allegro_container->Init(*this->my_user_data);  //se puede ver de pedirla por allegro, el tema es que no estaría iniciado todavía

	if (healthy_initialization)
	{
		this->my_communication = new Communication(this->my_user_data);  //Initialize the communication
		healthy_initialization = this->my_communication->is_the_connection_healthy();  //Checks if the communication process was successful
	}

	this->my_fsm = new FSM(this->my_user_data);
	this-> my_event_handler = new EventHandler(this->my_allegro_container,this->my_user_data);

	this->add_all_observers();

	return healthy_initialization;
};

void Resources::add_all_observers() {

	this->my_scenario->add_observer(new ScenarioDrawingObserver(this->my_scenario, this->my_drawing_manager));
	this->my_scenario->add_observer(new ScenarioEventsObserver(this->my_event_handler, this->my_scenario, this->my_fsm));


	this->my_fsm->add_observer(new FSMEventsObserver(this->my_event_handler, this->my_fsm, this->my_allegro_container,this->my_scenario));
	this->my_fsm->add_observer(new FSMCommunicationObserver(this->my_fsm, this->my_communication, this->my_scenario,this->my_user_data));
	this->my_fsm->add_observer(new FSMSceneObserver(this->my_fsm, this->my_scenario, this->my_event_handler, this->my_user_data));
	this->my_fsm->add_observer(new EventsCommunicationObserver(this->my_event_handler, this->my_communication, this->my_user_data,this->my_scenario));


}