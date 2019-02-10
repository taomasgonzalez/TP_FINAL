#include "LogicFSMEventsObserver.h"


LogicFSMEventsObserver::LogicFSMEventsObserver(LogicEventGenerator * event_gen, LogicFSM * fsm, Allegro* allegro_container, Userdata* data, Scene* scene)
{
	this->event_gen = event_gen;
	this->fsm = fsm;
	this->allegro_container = allegro_container;
	this->scenario = scene;
	this->my_user_data = data;
}

LogicFSMEventsObserver::~LogicFSMEventsObserver()
{
}

void LogicFSMEventsObserver::update() {
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
		this->event_gen->empty_all_queues();
		scenario->finish_game();
	}

	if (fsm->ld_game_over) {
		this->event_gen->append_new_event(new GAME_OVER_EventPackage(), (int) LogicEventGenerator::LogicQueues::soft);
	}

	if (fsm->ld_play_again) {
		this->event_gen->append_new_event(new PLAY_AGAIN_EventPackage(), (int)LogicEventGenerator::LogicQueues::soft);
	}



	if (fsm->receive_name) {
		EventPackage* his_new_name_package=this->fsm->get_fsm_ev_pack();
		unsigned char his_namelenght = ((NAME_IS_EventPackage *)his_new_name_package)->get_name_lenght();
		char * his_name = ((NAME_IS_EventPackage *)his_new_name_package)->give_me_your_name();

		my_user_data->my_network_data.tell_me_his_name(his_name, his_namelenght);

	}
	
}

	
