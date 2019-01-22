#include "ScenarioEventsObserver.h"

ScenarioEventsObserver::ScenarioEventsObserver(EventHandler * event_gen, Scene * scenario)
{
	this->my_event_handler = event_gen;
	this->scenario = scenario;
}


ScenarioEventsObserver::~ScenarioEventsObserver()
{
}

void ScenarioEventsObserver::update() {
	if (this->scenario->should_init) {
		EventPackage * evento_de_inicializion = new EventPackage();
		evento_de_inicializion->ev = Event::START_COMMUNICATION;
		this->my_event_handler->soft_queue->push(evento_de_inicializion);
		this->scenario->should_init = false;
	}

	if (scenario->should_the_action_be_checked()) {

		EventPackage* old_pack = my_event_handler->get_fsm_ev_pack(); //ac´´a ya paso por la fsm el chequeo tiene que ser previo

		if (scenario->action_is_possible(my_event_handler->get_fsm_ev_pack())) {
			
			EventPackage* new_ev_pack = new EventPackage();
			*new_ev_pack = *old_pack;
			if (old_pack->ev == Event::EXTERN_ACTION_REQUESTED)		//logica a poner en action_is_possible
				new_ev_pack->ev = Event::EXTERN_ACTION_ACCEPTED;
			else if (old_pack->ev == Event::LOCAL_ACTION_REQUESTED)
				new_ev_pack->ev = Event::LOCAL_ACTION;

			my_event_handler->append_new_soft_event(scenario->give_me_my_checked_package());
		}
		else {
			/*esto en teoria es innecesario, pero lo hacemos para mayor claridad,
			para que pueda haber tanto eventos de tipo EXTERN_ACTION_ACCEPTED
			como EXTERN_ACTION_DENIED y sean los dos procesados por la fsm*/
			if (old_pack->ev == Event::EXTERN_ACTION_REQUESTED)
				old_pack->ev = Event::EXTERN_ACTION_DENIED;
			else if (old_pack->ev == Event::LOCAL_ACTION_REQUESTED)  //Esto implica que hubo un error, se debe manda ERROR
				old_pack->ev = Event::LOCAL_ACTION_DENIED;

			my_event_handler->append_new_soft_event(old_pack);
		}
	}
}
