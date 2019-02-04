#pragma once
#include "EventGenerator.h"


class LogicEventGenerator : public EventGenerator
{
	enum class Queues {allegro, net, soft};
public:
	LogicEventGenerator(Allegro * al, Userdata* data);
	~LogicEventGenerator();

	friend class CommunicationEventsObserver;
	friend class ScenarioEventsObserver;
	friend class FSMEventsObserver;

	EventPackage* fetch_event();
	void empty_all_queues();

private:
	void append_all_queues();
	ALLEGRO_EVENT_QUEUE * al_queue;
	std::queue<EventPackage*>* allegro_queue;
	std::queue<EventPackage*>* soft_queue;		//cola para eventos de software.
	std::queue<EventPackage*>* net_queue;		//cola para eventos de networking.

	Userdata * my_user_data; //PQ tienne este puntero? lo necesita realmente?
	ALLEGRO_TIMER * time_out_timer;  // has to be moved to allegro.cpp??

	unsigned int time_out_count;
	void update_from_allegro_events();

};

