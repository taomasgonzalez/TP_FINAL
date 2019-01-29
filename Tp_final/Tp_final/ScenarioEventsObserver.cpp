#include "ScenarioEventsObserver.h"

ScenarioEventsObserver::ScenarioEventsObserver(EventHandler * event_gen, Scene * scenario,FSM * fsm)
{
	this->my_event_handler = event_gen;
	this->scenario = scenario;
	this->my_fsm = fsm;
}


ScenarioEventsObserver::~ScenarioEventsObserver()
{
}

void ScenarioEventsObserver::update() {

	if (this->scenario->game_started)
	{
		if(this->my_event_handler->my_user_data->my_network_data.is_client()==false)  //si es cliente carga el paquete que inicia la fsm
		this->my_event_handler->soft_queue->push(new START_COMMUNICATION_EventPackage(true));
	}

	if (scenario->check_local_action)  //lo llamo para chequear un evento de allegro antes de ponerlo en la cola de allegro
	{

		EventPackage* event_to_be_checked = this->scenario->give_me_my_allegro_event(); 

		if (event_to_be_checked != NULL)
		{
			this->scenario->is_the_action_possible(event_to_be_checked);//mando a analizar el EventPackage que llego desde allegro

			if (event_to_be_checked->is_this_a_valid_action() == true) //es una jugada válida, se carga la jugada en la cola
				my_event_handler->append_new_allegro_event(event_to_be_checked);

			if (event_to_be_checked->is_this_a_valid_action() == false) //no es un jugada válida, se carga error externo en vez de la jugada recibida
				my_event_handler->append_new_allegro_event(new ERROR_EventPackage(false));

		}
		else
		{
			std::cout << "Error interno, no llego el evento de allegro" << std::endl;
		}
	}
}
