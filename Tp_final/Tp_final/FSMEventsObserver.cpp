#include "FSMEventsObserver.h"



FSMEventsObserver::FSMEventsObserver(EventGenerator * event_gen, FSM * fsm, Allegro* allegro_container, Scene* scenario)
{
	this->event_gen = event_gen;
	this->fsm = fsm;
	this->allegro_container = allegro_container;
	this->scenario = scenario;
}

FSMEventsObserver::~FSMEventsObserver()
{
}

void FSMEventsObserver::update() {
	//me fijo si tengo que inicializar un time out timer porque acabo de mandar un paquete siendo server.
	if (fsm->new_ack_time_out) {
		if (!(fsm->waiting_for_ack)){
			fsm->waiting_for_ack = true;
		}
		allegro_container->append_time_out_timer();	//agrego el nuevo timer
		allegro_container->start_front_timer();		//lo inicio
	}

	//me fijo si tengo que eliminar un timer de ack porque acabo de recibirlo
	if (fsm->reset_ack_timer) {
		allegro_container->dequeu_time_out_timer();		

		if (allegro_container->no_time_outs())		//me fijo si ya no toy esperando ningun ack mas
			fsm->waiting_for_ack = false;
	}

	if(fsm->end_game){
		//vacio las colas. Nada importa ya porque el juego va a terminar. :(
		event_gen->net_queue->empty();
		event_gen->soft_queue->empty();				
	}

	/*if (fsm->check_action) {  Ya se hace en ScenarioEventsObserver::update(), fijarse donde corresponde
		EventPackage* old_pack =  fsm->get_fsm_ev_pack();
		if (scenario->is_the_action_possible()) {				//Esto debería estar implementado dentro the action is possible, deberia recibir y devolver un EventPackage
			EventPackage* new_ev_pack = new EventPackage();
			*new_ev_pack = *old_pack;
			if(old_pack->ev == My_Event::EXTERN_ACTION_REQUESTED)
				new_ev_pack->ev = My_Event::EXTERN_ACTION_ACCEPTED;
			else if(old_pack->ev == My_Event::LOCAL_ACTION_REQUESTED)
				new_ev_pack->ev = My_Event::LOCAL_ACTION;

			event_gen->append_new_soft_event(new_ev_pack);
		}
		else{
			/*esto en teoria es innecesario, pero lo hacemos para mayor claridad, 
			para que pueda haber tanto eventos de tipo EXTERN_ACTION_ACCEPTED
			como EXTERN_ACTION_DENIED y sean los dos procesados por la fsm*//*
			if (old_pack->ev == My_Event::EXTERN_ACTION_REQUESTED)
				old_pack->ev = My_Event::EXTERN_ACTION_DENIED;
			else if(old_pack->ev == My_Event::LOCAL_ACTION_REQUESTED)  //Esto implica que hubo un error, se debe manda ERROR
				old_pack->ev = My_Event::LOCAL_ACTION_DENIED;

			event_gen->append_new_soft_event(old_pack);
		}*/
	}

	
