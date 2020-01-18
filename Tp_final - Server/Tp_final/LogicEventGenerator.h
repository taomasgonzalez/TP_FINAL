#pragma once
#include "EventGenerator.h"

#define LOGIC_EV_GEN_AMOUNT_EV_PACKS	2


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
	
	//allegro queue for the timer to fetch keyboard events
	ALLEGRO_EVENT_QUEUE * al_key_queue = NULL;

	//allegro queue for the timer that blocks events
	ALLEGRO_EVENT_QUEUE * al_key_blocking_queue = NULL;

	ALLEGRO_TIMER * time_out_timer = NULL;

	//Timer to control the fething of keyboard events
	ALLEGRO_TIMER* keyboard_events_timer = NULL;

	//Timer to prevent fetching when a logic action is taking place
	ALLEGRO_TIMER* blocking_movements_events_timer = NULL;

	//Timer to prevent fetching too many attacks (TO BE IMPLEMENTED)
	ALLEGRO_TIMER* blocking_attacks_events_timer = NULL;


	//unsigned int time_out_count; not in use

	//Methods
	EventPackage * direction_to_event_package(Action_type action);
	void update_from_allegro_events();
	void update_from_allegro_timer_events();
	void update_from_allegro_keyboard_events();
	void update_keyboard_state(EventPackage* ev_packs[LOGIC_EV_GEN_AMOUNT_EV_PACKS]);

	//Pointers that allow the connection between the EventGenerator and Allego & Userdata
	Allegro* al = NULL;
	Userdata* my_user_data = NULL;


	//flags to detect the kind of movement in LogicEventGenerator::update_keyboard_state()
	bool jumping = false;
	bool attacking = false;
	bool acting = false;
	Direction_type side_move_dir = Direction_type::None;

	//Flag that indicates wether the game is in the playing screen or in another part of the program
	//It´s used to change the meaning of the keyboard events fetched
	bool are_we_playing = false;

	//Flag so the program knows if a new movement should be fetched
	bool blocked_movements = false;

	//Flag so the program knows if a new movement should be fetched
	bool blocked_attacks = false;

};

