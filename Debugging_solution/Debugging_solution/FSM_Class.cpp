#include "FSM_Class.h"


FSM::FSM(Userdata * data) : Observable(){

	this->user_data = data;

}


/******************************************************************************
*******************************************************************************
					PRIVATE METHODS DEFINITIONS
*******************************************************************************

/**************************************************************
					run_fsm
**************************************************************/
/*
*This function runs the FSM with a given input.
*
*INPUT:
*The event that is hold in the edge that contains the action routine.
*
*OUTPUT:
*Void
*/
void FSM:: run_fsm(EventPackage * ev_pack)
{
	Event_type event1 = ev_pack->give_me_your_event_type();
	this->my_ev_pack = ev_pack;
	
	int event_pos = 0;
	while (((actual_state->at(event_pos)).event != event1) && ((actual_state->at(event_pos)).event != Event_type::END_OF_TABLE))
	{	
		event_pos++;
	}

	//genera evento de software en caso de haber encontrado un evento que no debería ocurrir en ese estado.s MANDAR ERROR, NO PUEDE LLEGAR UN MOVE AL PRINICIPIO XEJ
	//if (this->actual_state->event == My_Event::END_OF_TABLE) 
	//	this->check_for_incorrect_event(event1);			

	//Runs the functions related to that event
	((actual_state->at(event_pos)).fun_trans)(this);
	this->actual_state = ((actual_state->at(event_pos)).nextstate);

}

void FSM::check_for_incorrect_event(Event_type event) {
	//if(this->actual_state == this->Waiting..) {

	//}
}


EventPackage* FSM::get_fsm_ev_pack() {
	return this->my_ev_pack;
}

std::vector<edge_t> * FSM::give_me_the_actual_state() {

	return actual_state;
}

void FSM::expand_state(std::vector<edge_t>* to_be_expanded, edge_t expansion)
{
	std::vector<edge_t>::iterator it = (to_be_expanded->end()) - 1;
	to_be_expanded->insert(it, expansion);
}
