#pragma once
#include "Userdata.h" //Data usage
#include "Communication.h"
#include "Allegroclass.h"
#include "PackageInfo.h"
#include <queue> 




class EventGenerator
{
public:
	EventGenerator(Allegro * al);
	~EventGenerator();

	friend class CommunicationEventsObserver;
	friend class ScenarioEventsObserver;
	friend class FSMEventsObserver;

	bool get_should_check_for_new_messages();

	void set_should_check_for_new_messages(bool should_check);

	void append_new_net_event(EventPackage* new_ev_pack);
	void append_new_soft_event(EventPackage* new_ev_pack);

protected:
	
	ALLEGRO_EVENT_QUEUE * al_queue;				//cola para eventos de allegro
	std::queue<EventPackage*>* soft_queue;		//cola para eventos de software.
	std::queue<EventPackage*>* net_queue;		//cola para eventos de networking.
	ALLEGRO_TIMER * time_out_timer;  // has to be moved to allegro.cpp??

	EventPackage fetch_event_al();
	EventPackage fetch_event_net();
	EventPackage fetch_event_soft();

	static unsigned int time_out_count;

private:
	bool check_for_new_messages;

};

