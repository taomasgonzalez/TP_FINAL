#pragma once
#include "EventGenerator.h"

enum class Blocking_timer_type { Walking, Jumping, Attacking };


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

	//timers
	void active_blocking_timers(Blocking_timer_type timer);
	void turn_off_blocking_timers(Blocking_timer_type timer);

private:
	EventPackage * direction_to_event_package(Action_type action, Direction_type dir);
	ALLEGRO_EVENT_QUEUE * al_key_queue = NULL;
	ALLEGRO_TIMER * time_out_timer = NULL;

	ALLEGRO_TIMER* keyboard_events_timer = NULL;

	//Timer to prevent fetching when a logic action is taking place
	ALLEGRO_TIMER* blocking_movements_events_timer = NULL;

	//Timer to prevent fetching too many attacks (TO BE IMPLEMENTED)
	ALLEGRO_TIMER* blocking_attacks_events_timer = NULL;

	//Timer to control the execution of the movements
	ALLEGRO_TIMER* movements_tracking_timer = NULL;

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

	//Flag so the program knows if a new movement should be fetched
	bool blocked_movements = false;

	//Flag so the program knows if a new movement should be fetched
	bool blocked_attacks = false;

};

