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
	EventPackage * direction_to_event_package(Action_type action, Direction_type dir);
	ALLEGRO_EVENT_QUEUE * al_key_queue = NULL;
	ALLEGRO_TIMER * time_out_timer = NULL;

	ALLEGRO_TIMER* keyboard_events_timer = NULL;

	unsigned int time_out_count;

	void update_from_allegro_events();
	void update_from_allegro_keyboard_events();
	void update_from_allegro_timer_events();

	Allegro* al = NULL;
	Userdata* my_user_data = NULL;

#define LOGIC_EV_GEN_AMOUNT_EV_PACKS	2

	void update_keyboard_state(EventPackage* ev_packs[LOGIC_EV_GEN_AMOUNT_EV_PACKS]);
	Direction_type side_move_dir = Direction_type::None;
	bool jumping = false;

};

