#pragma once
#include "EventGenerator.h"


class LogicEventGenerator : public EventGenerator
{
	
public:
	enum class Queues { allegro, net, soft, TOTAL_QUEUES };

	LogicEventGenerator(Allegro * al, Userdata* data);
	~LogicEventGenerator();

	friend class CommunicationEventsObserver;
	friend class ScenarioEventsObserver;
	friend class FSMEventsObserver;

	EventPackage* fetch_event();
	void empty_all_queues();

private:
	ALLEGRO_EVENT_QUEUE * al_queue;

	Userdata * my_user_data; //PQ tienne este puntero? lo necesita realmente?
	ALLEGRO_TIMER * time_out_timer;  // has to be moved to allegro.cpp??

	unsigned int time_out_count;
	void update_from_allegro_events();

};

