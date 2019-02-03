#pragma once
#include "Userdata.h" //Data usage
#include "FSM_Class.h"
#include "Communication.h"
#include "Allegroclass.h"
#include "EventPackage.h"
#include <queue> 


class EventGenerator
{
public:

	EventGenerator(Allegro * al, Userdata* data);
	~EventGenerator();

	friend class CommunicationEventsObserver;
	friend class ScenarioEventsObserver;
	friend class FSMEventsObserver;

	//In case an error ocurred and there are pending events to be run by the fsm
	void empty_all_queues();

	void append_new_net_event(EventPackage* new_ev_pack);
	void append_new_soft_event(EventPackage* new_ev_pack);

	EventPackage * fetch_event_net();
	EventPackage * fetch_event_soft();
	EventPackage * fetch_event_al();


protected:
	

	ALLEGRO_EVENT_QUEUE * al_queue;				
	std::queue<EventPackage*>* soft_queue;		//cola para eventos de software.
	std::queue<EventPackage*>* net_queue;		//cola para eventos de networking.

	Userdata * my_user_data; //PQ tienne este puntero? lo necesita realmente?
	ALLEGRO_TIMER * time_out_timer;  // has to be moved to allegro.cpp??


	unsigned int time_out_count;

private:

};

