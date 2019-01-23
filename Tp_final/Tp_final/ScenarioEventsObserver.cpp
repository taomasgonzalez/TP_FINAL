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
	if (this->scenario->should_init)
	{
		this->my_event_handler->soft_queue->push(new START_COMMUNICATION_EventPackage(true));
		this->scenario->should_init = false;
	}

	if (scenario->should_the_action_be_checked()) 
	{

		EventPackage* old_pack = this->my_fsm->get_fsm_ev_pack(); //aca ya paso por la fsm el chequeo tiene que ser previo

		if(scenario->is_the_action_possible(old_pack))
			my_event_handler->append_new_soft_event(scenario->give_me_my_checked_package());

		/*
		
		if (scenario->is_the_action_possible(my_event_handler->get_fsm_ev_pack())) {
			
			EventPackage* new_ev_pack = NULL; 
			if (old_pack->give_me_your_event_type() == My_event::EXTERN_ACTION_RECEIVED)		//logica a poner en is_the_action_possible
				new_ev_pack = new EXTERN_ACTION_ACCEPTED_EventPackage;

			else if (old_pack->give_me_your_event_type() == My_event::LOCAL_ACTION_REQUESTED)
				new_ev_pack = new LOCAL_ACTION_ACCEPTED_EventPackage(old_pack);

			my_event_handler->append_new_soft_event(scenario->give_me_my_checked_package());
		}
		else {
			/*esto en teoria es innecesario, pero lo hacemos para mayor claridad,
			para que pueda haber tanto eventos de tipo EXTERN_ACTION_ACCEPTED
			como EXTERN_ACTION_DENIED y sean los dos procesados por la fsm*//*
			if (old_pack->ev == My_Event::EXTERN_ACTION_REQUESTED)
				old_pack->ev = My_Event::EXTERN_ACTION_DENIED;
			else if (old_pack->ev == My_Event::LOCAL_ACTION_REQUESTED)  //Esto implica que hubo un error, se debe manda ERROR
				old_pack->ev = My_Event::LOCAL_ACTION_DENIED;

			my_event_handler->append_new_soft_event(old_pack);
		}*/
	}
}
