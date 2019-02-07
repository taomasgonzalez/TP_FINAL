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
	set_fsm_ev_pack(ev_pack);

	while ((this->actual_state->event != event1) && (this->actual_state->event != Event_type::END_OF_TABLE))
	{	
		this->actual_state++;
	}

	//genera evento de software en caso de haber encontrado un evento que no debería ocurrir en ese estado.s MANDAR ERROR, NO PUEDE LLEGAR UN MOVE AL PRINICIPIO XEJ
	//if (this->actual_state->event == My_Event::END_OF_TABLE) 
	//	this->check_for_incorrect_event(event1);			

	//Runs the functions related to that event
	(this->actual_state->fun_trans)(this);
	this->actual_state = (this->actual_state->nextstate);

}

void FSM::check_for_incorrect_event(Event_type event) {
	//if(this->actual_state == this->Waiting..) {

	//}
}


void FSM::copy_event(edge_t* to_copy, edge_t* to_be_copied, int length) {
	for (int i = 0; i < length; i++)
	{
		to_copy[i].event = to_be_copied[i].event;
		to_copy[i].nextstate = to_be_copied[i].nextstate;
		to_copy[i].fun_trans = to_be_copied[i].fun_trans;
	}
}

EventPackage* FSM::get_fsm_ev_pack() {
	return this->my_ev_pack;
}

void FSM::set_fsm_ev_pack(EventPackage * new_ev_pack)
{
	delete my_ev_pack;
	my_ev_pack = new_ev_pack;
}

edge_t * FSM::give_me_the_actual_state() {

	return this->actual_state;
}

