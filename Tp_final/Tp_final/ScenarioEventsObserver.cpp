#include "ScenarioEventsObserver.h"

ScenarioEventsObserver::ScenarioEventsObserver(LogicEventGenerator * event_gen, Scene * scenario,FSM * fsm, Userdata * data)
{
	this->ev_gen = event_gen;
	this->scenario = scenario;
	this->my_fsm = fsm;
	this->my_user_data = data;
}


ScenarioEventsObserver::~ScenarioEventsObserver()
{
}

void ScenarioEventsObserver::update() {

	if (this->scenario->game_started)
	{
		if (this->my_user_data->my_network_data.is_client() == false)  //si es cliente carga el paquete que inicia la fsm
			ev_gen->append_new_event(new START_COMMUNICATION_EventPackage(), (int) LogicEventGenerator::Queues::soft);
		this->scenario->initializing = true;
	}
	if (this->scenario->enemys_ready)
	{
		ev_gen->append_new_event(new ENEMYS_LOADED_EventPackage(),(int) LogicEventGenerator::Queues::soft);
	}
	if (this->scenario->we_won)
	{
		if (!my_user_data->my_network_data.is_client()) //we do this ckeck here because in scene we don´t have that info
			ev_gen->append_new_event(new WE_WON_EventPackage(), (int)LogicEventGenerator::Queues::soft);
	}
	if (this->scenario->we_lost)
	{
		if (!my_user_data->my_network_data.is_client()) //we do this ckeck here because in scene we don´t have that info
			ev_gen->append_new_event(new GAME_OVER_EventPackage(), (int)LogicEventGenerator::Queues::soft);
	}

	//if (scenario->check_local_action)  //lo llamo para chequear un evento de allegro antes de ponerlo en la cola de allegro
	//{

	//	EventPackage* event_to_be_checked = this->scenario->give_me_my_allegro_event(); 

	//	if (event_to_be_checked != NULL)
	//	{
	//		this->scenario->is_the_action_possible(event_to_be_checked);//mando a analizar el EventPackage que llego desde allegro

	//		if (event_to_be_checked->is_this_a_valid_action() == true) //es una jugada válida, se carga la jugada en la cola
	//			my_event_handler->append_new_allegro_event(event_to_be_checked);

	//		if (event_to_be_checked->is_this_a_valid_action() == false) //no es un jugada válida, se carga error externo en vez de la jugada recibida
	//			my_event_handler->append_new_allegro_event(new ERROR_EventPackage(false));

	//	}
	//	else
	//	{
	//		std::cout << "Error interno, no llego el evento de allegro" << std::endl;
	//	}
	//}
}
