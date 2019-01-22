#include "Resources.h"


Resources::Resources() {

	this->scenario = new Scene;
	this->drawing_manager = new Drawer;
	this->allegro_container = new Allegro;
	this->my_user_data = new Userdata;
};

Resources::~Resources() {  //Delete all the resources loaded

	delete this->scenario;
	delete this->drawing_manager;
	delete this->allegro_container;
	delete this->my_user_data;
	delete this->communication;

};


bool Resources::Intialize_all_the_resources() {

	bool healthy_initialization = true;

	this->communication = new Communication(this->my_user_data->ip);  //Initialize the communication
	if( this->communication->is_the_connection_healthy())  //Checks if the communication process was successful
	//CHEQUEAR QUE SI PONELE NO ANDUVO LA COM PERO SI ALLEGRO EL PROGRAMA CORRE IGUAL
	healthy_initialization = this->allegro_container->Init(*this->my_user_data);

	return healthy_initialization;
};

void Resources::add_all_observers(EventHandler * my_event_handler) {

	this->scenario->add_observer(this->drawing_manager);
	this->communication->add_observer(new EventsCommunicationObserver(my_event_handler, this->communication)); //????

	my_event_handler->add_observer(new FSMEventsObserver(my_event_handler, my_event_handler, this->allegro_container,this->scenario)); 
	//pointer to fsm and to event generator is the same because eventgenerator is an fsm, check

	my_event_handler->add_observer(new FSMCommunicationObserver(my_event_handler, this->communication, this->scenario));
	my_event_handler->add_observer(new FSMSceneObserver(my_event_handler, this->scenario));
	my_event_handler->add_observer(new EventsCommunicationObserver(my_event_handler, this->communication));
	this->scenario->add_observer(new ScenarioEventsObserver(my_event_handler, this->scenario));


}