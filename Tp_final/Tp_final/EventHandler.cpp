#include "EventHandler.h"


EventHandler::EventHandler(Allegro * al, bool is_client) :
 EventGenerator(al), Fsm(is_client)
{
}


EventHandler::~EventHandler()
{
}

void EventHandler::handle_event() {

	EventPackage ev_pack_soft = fetch_event_soft();
	if (ev_pack_soft.ev != Event::NO_EVENT)
		run_fsm(ev_pack_soft);

	EventPackage ev_pack_al = fetch_event_al();
	if ((ev_pack_al.ev != Event::NO_EVENT) && ev_pack_al.ev != Event::LOCAL_QUIT)
		run_fsm(ev_pack_al);

	EventPackage ev_pack_net = fetch_event_net();
	if (ev_pack_net.ev != Event::NO_EVENT)
		run_fsm(ev_pack_net);


	set_should_check_for_new_messages(true);
	notify_obs();
}

