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
		
	}

	if (fsm->receive_name) {
		EventPackage* his_new_name_package=this->fsm->get_fsm_ev_pack();
		unsigned char his_namelenght = ((NAME_IS_EventPackage *)his_new_name_package)->get_name_lenght();
		char * his_name = ((NAME_IS_EventPackage *)his_new_name_package)->give_me_your_name();

		this->event_gen->my_user_data->my_network_data.tell_me_his_name(his_name, his_namelenght);

	}
	if (fsm->check_action) {

		EventPackage* event_to_be_checked = this->fsm->get_fsm_ev_pack();

		if (!this->my_scenario->is_the_action_possible(event_to_be_checked))//mando a analizar el EventPackage sea local 
		{
			if (event_to_be_checked->is_this_a_local_action() == false)
			{
				this->event_gen->empty_all_queues(); //hay que hacerla
				this->event_gen->append_new_soft_event(new ERROR_EventPackage(true));
			}

		}
		else
			this->my_scenario->execute_action(event_to_be_checked); //hay que hacerla
	}
		if (fsm->we_won) {

			EventPackage* event_to_be_checked = this->fsm->get_fsm_ev_pack();

			if (!this->my_scenario->did_we_win(event_to_be_checked))//mando a analizar el EventPackage sea local 
			{
				if (event_to_be_checked->is_this_a_local_action() == false)
				{
					this->event_gen->empty_all_queues(); //hay que hacerla
					this->event_gen->append_new_soft_event(new ERROR_EventPackage(true));
				}

			}
			else
				this->event_gen->append_new_soft_event(new WE_WON_EventPackage(true));

		}

		if (fsm->we_lost) {

			EventPackage* event_to_be_checked = this->fsm->get_fsm_ev_pack();

			if (!this->my_scenario->do_we_won(event_to_be_checked))//mando a analizar el EventPackage sea local 
			{
				if (event_to_be_checked->is_this_a_local_action() == false)
				{
					this->event_gen->empty_all_queues(); //hay que hacerla
					this->event_gen->append_new_soft_event(new ERROR_EventPackage(true));
				}

			}
			else
				this->event_gen->append_new_soft_event(new GAME_OVER_EventPackage(true));

		}
	
}

	
