#include "FSMEventsObserver.h"



FSMEventsObserver::FSMEventsObserver(EventGenerator * event_gen, Fsm * fsm)
{
	this->event_gen = event_gen;
	this->fsm = fsm;
}


FSMEventsObserver::~FSMEventsObserver()
{
}

void FSMEventsObserver::update() {
	//me fijo si tengo que inicializar un time out timer porque acabo de mandar un paquete siendo server.
	if (fsm->new_ack_time_out) {
		
		this->allegro_container->append_time_out_timer();	//agrego el nuevo timer
		this->allegro_container->start_front_timer();		//lo inicio

		fsm->new_ack_time_out = false;				//aclaro que ya agregue el nuevo timer.
	}

	//me fijo si tengo que eliminar un timer de ack porque acabo de 
	if (fsm->reset_ack_timer) {
		this->allegro_container->dequeu_time_out_timer();

		if (this->allegro_container->no_time_outs)
			fsm->waiting_for_ack = false;

		fsm->reset_ack_timer = false;
	}

	if(fsm->end_game){
		//vacio las colas. Nada importa ya porque el juego va a terminar.
		event_gen->net_queue->empty();
		event_gen->soft_queue->empty();				
	}
	
}