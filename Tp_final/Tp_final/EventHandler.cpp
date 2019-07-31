#include "EventHandler.h"


EventHandler::EventHandler(FSM * fsm, EventGenerator* ev_gen)
{
	this->fsm = fsm;
	this->ev_gen = ev_gen;
}


EventHandler::~EventHandler()
{
}

/******************************************
****************handle_event***************
*******************************************
*handle_event executes fetches one event from its event_queue and dispatches it through its FSM.
*	INPUT:
*		1) void.
*	OUTPUT:
*		void.
*/
void EventHandler::handle_event() {

	EventPackage * ev_pack = ev_gen->fetch_event();
	if (ev_pack->give_me_your_event_type() != Event_type::NO_EVENT)
		fsm->run_fsm(ev_pack);
	else
		delete ev_pack;

	return;

}

FSM * EventHandler::get_fsm()
{
	return fsm;
}

EventGenerator* EventHandler::get_ev_gen() {
	return ev_gen;
}
