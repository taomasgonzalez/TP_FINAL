#pragma once
#include "EventGenerator.h"


class LogicEventGenerator : public EventGenerator
{
	
public:
	

	LogicEventGenerator(Allegro * al, Userdata* data);
	~LogicEventGenerator();

	friend class CommunicationEventsObserver;
	friend class ScenarioEventsObserver;
	friend class FSMEventsObserver;

	EventPackage* fetch_event();
	void empty_all_queues();

private:

	Userdata * my_user_data;

	ALLEGRO_EVENT_QUEUE * al_key_queue;
	ALLEGRO_EVENT_QUEUE* coordinate_scene_events_queue;
	ALLEGRO_TIMER * time_out_timer;
	ALLEGRO_TIMER * coordinate_scene_events_timer;

	unsigned int time_out_count;

	void update_from_allegro_events();
	void update_from_allegro_keyboard_events();
	void update_from_allegro_timer_events();

};

