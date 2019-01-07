#include "FSMEventsObserver.h"



FSMEventsObserver::FSMEventsObserver(EventGenerator * event_gen, Fsm * fsm, Allegro* allegro_container)
{
	this->event_gen = event_gen;
	this->fsm = fsm;
	this->allegro_container = allegro_container;
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
		//vacio las colas. Nada importa ya porque el juego va a terminar.
		event_gen->net_queue->empty();
		event_gen->soft_queue->empty();				
	}
	
}