#include "LogicEventGenerator.h"
#include <iostream>

/******************************************
***************LogicEventGenerator*****************
*******************************************
* Constructor of the LogicEventGenerator class
*
*	INPUT:
*		1) Pointer to allegro class that manage the game
*		2) Pointer to Userdata class where the information of the user is saved
*	OUTPUT:
*		void.
*/
LogicEventGenerator::LogicEventGenerator(Allegro * al, Userdata* data) : EventGenerator()
{
	this->my_user_data = data;
	this->al = al;


	al_key_queue = al_create_event_queue();
	al_register_event_source(al_key_queue, al_get_keyboard_event_source());

	//every 100 ms the program looks for keyboard events
	keyboard_events_timer = al_create_timer(1 / 10.0);
	al_register_event_source(al_key_queue, al_get_timer_event_source(keyboard_events_timer));
	al_start_timer(keyboard_events_timer);


	al_key_blocking_queue= al_create_event_queue();
	//Set to random number, is not started until a blocking is needed and a new timer큦 speed is set
	blocking_movements_events_timer = al_create_timer(1 / 30.0);
	//block attacks for 200 ms so they do not overload
	blocking_attacks_events_timer = al_create_timer(0.2);

	al_register_event_source(al_key_blocking_queue, al_get_timer_event_source(blocking_movements_events_timer));
	al_register_event_source(al_key_blocking_queue, al_get_timer_event_source(blocking_attacks_events_timer));



	//time_out_timer = al->get_front_time_out_timer();
	//time_out_count = 0;
	//al_start_timer(coordinate_scene_events_timer);
	append_all_queues((int)LogicQueues::TOTAL_QUEUES);
}


LogicEventGenerator::~LogicEventGenerator()
{
}

/******************************************
***************fetch_event*****************
*******************************************
*fetch_event returns the new Logic Event to be exectuted by a Logic FSM.
*fetch_event returns one and only one EventPackage coming from one of the multiple event queues the LogicEventGenerator may have.
*fetch_event is designed in such a way that the queues take turns as to which of them will return the EventPackage.
*	INPUT:
*		1) void.
*	OUTPUT:
*		the next EventPackage to be executed by an FSM.
*/
EventPackage * LogicEventGenerator::fetch_event()
{
	update_from_allegro_events();
	return EventGenerator::fetch_event();
}

/******************************************
********update_from_allegro_events*********
*******************************************
*update_from_allegro_events is an internal method that converts events inside an allegro event queue to
*EventPackages that represent the Logic function of that allegro Event.
*update_from_allegro_events does this by removign the allegro event from the allegro event queue.
*	INPUT:
*		1) void.
*	OUTPUT:
*		void.
*/
void LogicEventGenerator::update_from_allegro_events() {

	update_from_allegro_timer_events(); 
	update_from_allegro_keyboard_events();

}

/******************************************
********update_from_allegro_timer_events*********
*******************************************
*update_from_allegro_timer_events is an internal method that analyze events inside an allegro event queue linked
*to timer events of blokcing movements and attacks
*
*	INPUT:
*		1) void.
*	OUTPUT:
*		void.
*/
void LogicEventGenerator::update_from_allegro_timer_events() {

	ALLEGRO_EVENT  allegroEvent;

	if (al_get_next_event(al_key_blocking_queue, &allegroEvent)) {			//fetch from the queue if it큦 not empty

		if (this->are_we_playing) 
		{
			if (allegroEvent.type == ALLEGRO_EVENT_TIMER)
			{
				if (allegroEvent.timer.source == blocking_movements_events_timer)
				{
					this->blocked_movements = false; //the block  must finish, allowing new movements events to be fetched
					al_stop_timer(blocking_movements_events_timer);
				}

				//if (allegroEvent.timer.source == blocking_attacks_events_timer) //to be implemented
				//{
				//	this->blocked_attacks = false; //the block  must finish, allowing new attacking events to be fetched
				//	al_stop_timer(blocking_attacks_events_timer);
				//}
			}
		}
		else
			int i = 0;
		//here we will put the fetching events when we are not playing, such as when we enter our username
		//IP, etc


	}

	//viejo
	//ALLEGRO_EVENT allegroEvent;
	//EventPackage * ev_pack = NULL;

	//if (al_get_next_event(coordinate_scene_events_queue, &allegroEvent)) {
	//	if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
	//		if (allegroEvent.timer.source == coordinate_scene_events_timer) {
	//		}
	//		else if (allegroEvent.timer.source == time_out_timer) {

	//		}
	//	}
	//}

}

/******************************************
********update_from_allegro_keyboard_events*********
*******************************************
*update_from_allegro_timer_events is an internal method that analyze events inside an allegro event queue linked
*to keyboard events of moving and attacking from the player
*
*	INPUT:
*		1) void.
*	OUTPUT:
*		void.
*/
void LogicEventGenerator::update_from_allegro_keyboard_events() {
	ALLEGRO_EVENT  allegroEvent;
	EventPackage * ev_packs[LOGIC_EV_GEN_AMOUNT_EV_PACKS] = { NULL, NULL};

	if (al_get_next_event(al_key_queue, &allegroEvent)) {			//tomo de la cola en caso de que no este vacia

		if (allegroEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//debo mandar error porque cerraron la pantalla				
			ev_packs[0] = new ERROR_EventPackage();
		}
		if (this->are_we_playing)
		{
			if (allegroEvent.type == ALLEGRO_EVENT_TIMER)
			{
				if (allegroEvent.timer.source == keyboard_events_timer)
					update_keyboard_state(ev_packs);

				//The buffer of the allegro큦 keyboard is flushed due to possible unwanted duplicated events
				//The buffer is cleaned every ALLEGRO_EVENT_TIMER that is linked with the refresh rate of fetching an allegro keyboard event
				al_flush_event_queue(al_key_queue);

			}
		}
		else
			int i=0; 
			//here we will put the fetching events when we are not playing, such as when we enter our username
			//IP, etc
		
		
	}

	for(int i =0; i < LOGIC_EV_GEN_AMOUNT_EV_PACKS; i++)
		if (ev_packs[i] != NULL)
			append_new_event(ev_packs[i], (int)LogicQueues::allegro);

}

/******************************************
********update_keyboard_state*********
*******************************************
*update_keyboard_state is an internal method that fetchs keyboards events if there are not currently actived blocking process
*
*	INPUT:
*		1) Pointer to EventPackage to save the fetched events
*	OUTPUT:
*		void.
*/
void LogicEventGenerator::update_keyboard_state(EventPackage* ev_packs[LOGIC_EV_GEN_AMOUNT_EV_PACKS]) {
	ALLEGRO_KEYBOARD_STATE keystate;
	al_get_keyboard_state(&keystate);

	if (!this->blocked_movements) 
	{
		if (al_key_down(&keystate, ALLEGRO_KEY_UP)) //Check if jumping
		{
			this->jumping = true;
			this->acting = true;
			//A jump movement lasts 1.2s so we block the fetching of movements until 50ms before it큦 finished
			al_set_timer_speed(blocking_movements_events_timer, 1.15);
			al_start_timer(blocking_movements_events_timer);
			this->blocked_movements = true;
		}


		if (al_key_down(&keystate, ALLEGRO_KEY_LEFT)) //Check if moving to the left
		{
			this->side_move_dir = Direction_type::Left;
			this->acting = true;

			if (!this->jumping) //If the user wants to move without jumping
			{
				//A movement lasts 0.3s so we block the fetching of movements until 50ms before it큦 finished
				al_set_timer_speed(blocking_movements_events_timer, 0.25);
				al_start_timer(blocking_movements_events_timer);
				this->blocked_movements = true;
			}
		}
		else if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT)) //Check if moving to the right
		{
			this->side_move_dir = Direction_type::Right;
			this->acting = true;

			if (!this->jumping) //If the user wants to move without jumping
			{
				//A movement lasts 0.3s so we block the fetching of movements until 50ms before it큦 finished
				al_set_timer_speed(blocking_movements_events_timer, 0.25);
				al_start_timer(blocking_movements_events_timer);
				this->blocked_movements = true;
			}
		}
	}

	if (al_key_down(&keystate, ALLEGRO_KEY_SPACE)	&&	!this->blocked_attacks) //Check if attacking
	{
		this->attacking = true;
		this->acting = true;
		//al_start_timer(blocking_attacks_events_timer);
		//this->blocked_attacks=true;

	}

	if (acting) //New movements should be appended to the array
	{
		int actual_ev_pack = 0;

		if(this->side_move_dir != Direction_type::None || this->jumping) //a movement is appended to the array
			ev_packs[actual_ev_pack++] = direction_to_event_package(Action_type::Move);

		if(attacking) //an attack is appended to the array
			ev_packs[actual_ev_pack] = direction_to_event_package(Action_type::Attack);
	}
	
	//Flags are cleaned
	this->side_move_dir = Direction_type::None;
	this->acting = false;
	this->attacking = false;
	this->jumping = false;

}

/******************************************
********direction_to_event_package*********
*******************************************
*direction_to_event_package is an internal method that translates the action to it큦 appropiate EventPackage
*
*	INPUT:
*		1) Action_type action - Action to be translate
*	OUTPUT:
*		EventPackage* - EventPackage linked to the action received
*/

EventPackage* LogicEventGenerator::direction_to_event_package(Action_type action) {
	EventPackage* ev_pack = NULL;

	if (action == Action_type::Move && this->jumping) {
		//the player is jumping in one direction, so should first convert to the suited Direction_type
		if (this->side_move_dir != Direction_type::None)
			this->side_move_dir = (this->side_move_dir == Direction_type::Left) ? Direction_type::Jump_Left : Direction_type::Jump_Right;
		else
			this->side_move_dir = Direction_type::Jump_Straight;
	}

	if (!my_user_data->my_network_data.is_client()) {
		if (action == Action_type::Attack)
			ev_pack = new ATTACK_EventPackage();
		else  if (action == Action_type::Move && this->side_move_dir != Direction_type::None)
			ev_pack = new MOVE_EventPackage(this->side_move_dir);
	}
	else if (this->side_move_dir != Direction_type::None)
		ev_pack = new ACTION_REQUEST_EventPackage(action, this->side_move_dir);
	else if (action == Action_type::Attack)
		ev_pack = new ACTION_REQUEST_EventPackage(action, this->side_move_dir);

	return ev_pack;
}


/******************************************
***************empty_all_queues************
*******************************************
*empty_all_queues empties all the event_queues the LogicEventGenerator has so that no new events will come unless
*they are placed on any queue after the call to this function.
*	INPUT:
*		1) void.
*	OUTPUT:
*		void.
*/
void LogicEventGenerator::empty_all_queues() {
	EventGenerator::empty_all_queues();
	al_flush_event_queue(al_key_queue);
}
