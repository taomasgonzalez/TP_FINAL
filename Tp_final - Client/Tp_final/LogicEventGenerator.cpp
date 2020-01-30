#include "LogicEventGenerator.h"
#include <conio.h>
#include <allegro5/allegro.h>
#include <iostream>

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_R
};

using namespace std;
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


	al_key_timers_queue = al_create_event_queue();

	//every FPS the program looks for keyboard events
	keyboard_events_timer = al_create_timer(2 / FPS);
	movements_tracking_timer = al_create_timer(0.3);

	al_register_event_source(al_key_timers_queue, al_get_timer_event_source(movements_tracking_timer));
	al_register_event_source(al_key_timers_queue, al_get_timer_event_source(keyboard_events_timer));
	al_start_timer(keyboard_events_timer);

	//Set to random number, is not started until a blocking is needed and a new timer´s speed is set
	blocking_movements_events_timer = al_create_timer(1 / 30.0);
	//block attacks for 200 ms so they do not overload
	blocking_attacks_events_timer = al_create_timer(0.1);

	al_register_event_source(al_key_timers_queue, al_get_timer_event_source(blocking_movements_events_timer));
	al_register_event_source(al_key_timers_queue, al_get_timer_event_source(blocking_attacks_events_timer));


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
*update_from_allegro_events does this by removing the allegro event from the allegro event queue.
*	INPUT:
*		1) void.
*	OUTPUT:
*		void.
*/
void LogicEventGenerator::update_from_allegro_events() {

	update_from_allegro_timer_events();

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

	while (al_get_next_event(al_key_timers_queue, &allegroEvent)) {			//fetch from the queue if it´s not empty

		if (this->are_we_playing)
		{
			if (allegroEvent.type == ALLEGRO_EVENT_TIMER)
			{

				if (allegroEvent.timer.source == blocking_movements_events_timer)
				{
					this->blocked_movements = false; //the block  must finish, allowing new movements events to be fetched
					std::cout << "Termino el bloqueo por el movimiento" << std::endl;
					al_stop_timer(blocking_movements_events_timer);//the timer is stopped

				}

				else if (allegroEvent.timer.source == keyboard_events_timer) // FPS event, the state of the keys must be refresh
				{
					update_from_allegro_keyboard_events();
				}

				else if (allegroEvent.timer.source == blocking_attacks_events_timer) //to be implemented
				{
					this->blocked_attacks = false; //the block must finish, allowing new attacking events to be fetched
					std::cout << "Termino el bloqueo de ataques" << std::endl;
					al_stop_timer(blocking_attacks_events_timer);
				}

					load_events_from_keyboard();
			}
		}
		else
			int i = 0;
		//here we will put the fetching events when we are not playing, such as when we enter our username
		//IP, etc


	}


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
	EventPackage * ev_packs = NULL;

	while (al_get_next_event(al_key_queue, &allegroEvent)) { //All the key events are fetched, all the keys´ states are refreshed

		if (allegroEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//debo mandar error porque cerraron la pantalla				
			ev_packs = new ERROR_EventPackage();
			break;
		}

		update_key_state(allegroEvent);

	}
}



/******************************************
********update_key_state*********
*******************************************
*update_keyboard_state is an internal method that updates the saved local state of a key
*
*	INPUT:
*		1) ALLEGRO_EVENT allegroEvent
*	OUTPUT:
*		void.
*/
void LogicEventGenerator::update_key_state(ALLEGRO_EVENT allegroEvent) {


	//Checks is the keys are pressed
	if (allegroEvent.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (allegroEvent.keyboard.keycode) {
		case ALLEGRO_KEY_UP:

			key[KEY_UP] = true;
			std::cout << "Se apreto UP" << std::endl;
			//ev_pack = direction_to_event_package(Action_type::Move, Direction_type::Jump_Straight);
			//A jump movement lasts 1.2s so we block the fetching of movements until 50ms before it´s finished
			//al_set_timer_speed(blocking_movements_events_timer, 1.15);
			break;

		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = true;
			std::cout << "Se apreto DOWN" << std::endl;
			break;

		case ALLEGRO_KEY_LEFT:
			key[KEY_LEFT] = true;
			std::cout << "Se apreto LEFT" << std::endl;

			//ev_pack = direction_to_event_package(Action_type::Move, Direction_type::Left);
			//al_set_timer_speed(blocking_movements_events_timer, 0.25);
			break;

		case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = true;
			std::cout << "Se apreto RIGHT" << std::endl;

			//ev_pack = direction_to_event_package(Action_type::Move, Direction_type::Right);
			//al_set_timer_speed(blocking_movements_events_timer, 0.25);
			break;

		case ALLEGRO_KEY_SPACE:
			key[KEY_SPACE] = true;
			std::cout << "Se apreto SPACE" << std::endl;

			break;

		case ALLEGRO_KEY_R:
			key[KEY_R] = true;
			std::cout << "Se apreto R" << std::endl;

			//ev_pack = new RESET_EventPackage(true);
			break;

		default:
			std::cout << "Not an expected key was pressed" << std::endl;
		}
	}

	//Checks is the keys are released
	if (allegroEvent.type == ALLEGRO_EVENT_KEY_UP) {
		switch (allegroEvent.keyboard.keycode) {

		case ALLEGRO_KEY_UP:
			key[KEY_UP] = false;
			std::cout << "Se solto UP" << std::endl;

			break;

		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = false;
			std::cout << "Se solto DOWN" << std::endl;

			break;

		case ALLEGRO_KEY_LEFT:
			key[KEY_LEFT] = false;
			std::cout << "Se solto LEFT" << std::endl;

			break;

		case ALLEGRO_KEY_RIGHT:
			std::cout << "Se solto RIGHT" << std::endl;
			key[KEY_RIGHT] = false;
			break;

		case ALLEGRO_KEY_SPACE:
			std::cout << "Se solto SPACE" << std::endl;
			key[KEY_SPACE] = false;
			break;

		case ALLEGRO_KEY_R:
			key[KEY_R] = false;
			break;

		default:
			std::cout << "Not an expected key was released" << std::endl;
		}
	}

	//if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_SPACE && !this->blocked_attacks)
	//{
	//	ev_pack = direction_to_event_package(Action_type::Attack);
	//	//al_start_timer(blocking_attacks_events_timer);
	//}


	//return ev_pack;

}

/******************************************
********load_events_from_keyboard*********
*******************************************
*load_events_from_keyboard is an internal method that checks the actual state of the keys of the keyboard, so
*in case that a move needs to be started/ continued(the key was never released) the correct event is appended
*
*	INPUT:
*		void
*	OUTPUT:
*		void.
*/
void LogicEventGenerator::load_events_from_keyboard() {

	EventPackage* ev_pack = NULL;


	if (this->are_we_playing) //Events related to playing mode just as attacks and movements
	{
		if (!this->blocked_movements)
		{
			if (key[KEY_UP])
			{
				if (key[KEY_LEFT])
				{
					append_new_event(direction_to_event_package(Action_type::Move, Direction_type::Jump_Left), (int)LogicQueues::allegro);
					//A jump movement lasts 1.2s so we block the fetching of movements until 50ms before it´s finished
					al_set_timer_speed(blocking_movements_events_timer, 10.8);
					std::cout << "Se mando un JUMP LEFT" << std::endl;

				}
				else if (key[KEY_RIGHT])
				{
					append_new_event(direction_to_event_package(Action_type::Move, Direction_type::Jump_Right), (int)LogicQueues::allegro);
					//A jump movement lasts 1.2s so we block the fetching of movements until 50ms before it´s finished
					al_set_timer_speed(blocking_movements_events_timer,0.8);
					std::cout << "Se mando un JUMP RIGHT" << std::endl;
				}
				else
				{
					append_new_event(direction_to_event_package(Action_type::Move, Direction_type::Jump_Straight), (int)LogicQueues::allegro);
					//A jump movement lasts 1.2s so we block the fetching of movements until 50ms before it´s finished
					al_set_timer_speed(blocking_movements_events_timer, 0.8);
					std::cout << "Se mando un UP" << std::endl;

					//ev_pack = direction_to_event_package(Action_type::Move, Direction_type::Jump_Straight);
				}
			}

			else if (key[KEY_DOWN])
			{
				std::cout << "Se mando un DOWN" << std::endl;

			}

			else if (key[KEY_LEFT])
			{
				append_new_event(direction_to_event_package(Action_type::Move, Direction_type::Left), (int)LogicQueues::allegro);
				al_set_timer_speed(blocking_movements_events_timer, 0.3);
				std::cout << "Se mando un LEFT" << std::endl;

				//ev_pack = direction_to_event_package(Action_type::Move, Direction_type::Left);
			}

			else if (key[KEY_RIGHT])
			{
				append_new_event(direction_to_event_package(Action_type::Move, Direction_type::Right), (int)LogicQueues::allegro);
				al_set_timer_speed(blocking_movements_events_timer, 0.3);
				std::cout << "Se mando un RIGHT" << std::endl;

				//ev_pack = direction_to_event_package(Action_type::Move, Direction_type::Right);
			}
		}
		if (key[KEY_R])
		{
			append_new_event(new RESET_EventPackage(true), (int)LogicQueues::allegro);
			std::cout << "Se mando un RESET" << std::endl;
			key[0] = false;
			key[1] = false;
			key[2] = false;
			key[3] = false;
			key[4] = false;
			key[5] = false;

			//ev_pack = new RESET_EventPackage(true);
		}

		if (!this->blocked_attacks)
			if (key[KEY_SPACE])
			{
				append_new_event(direction_to_event_package(Action_type::Attack, Direction_type::Right), (int)LogicQueues::allegro);
				std::cout << "Se mando un ATTACK" << std::endl;
				al_start_timer(blocking_attacks_events_timer);
				this->blocked_attacks = true;
				//ev_pack = direction_to_event_package(Action_type::Attack, Direction_type::None);
			}
	}
	else //To load events related when the game is not currently playing
		int i;


	//if (ev_pack != NULL)
	//	append_new_event(ev_pack, (int)LogicQueues::allegro);

}


/******************************************
********direction_to_event_package*********
*******************************************
*direction_to_event_package is an internal method that translates the action to it´s appropiate EventPackage
*
*	INPUT:
*		1) Action_type action - Action to be translate
*	OUTPUT:
*		EventPackage* - EventPackage linked to the action received
*/

EventPackage* LogicEventGenerator::direction_to_event_package(Action_type action, Direction_type direction) {
	EventPackage* ev_pack = NULL;

	//Doesn´t make sense with the new implementation
	//if (action == Action_type::Move && this->jumping) {
	//	//the player is jumping in one direction, so should first convert to the suited Direction_type
	//	if (this->side_move_dir != Direction_type::None)
	//		this->side_move_dir = (this->side_move_dir == Direction_type::Left) ? Direction_type::Jump_Left : Direction_type::Jump_Right;
	//	else
	//		this->side_move_dir = Direction_type::Jump_Straight;
	//}

	if (!my_user_data->my_network_data.is_client()) {
		if (action == Action_type::Attack)
			ev_pack = new ATTACK_EventPackage();
		else  if (action == Action_type::Move && direction != Direction_type::None)
			ev_pack = new MOVE_EventPackage(direction);
	}
	else
	{
		if (action == Action_type::Attack)
			ev_pack = new ACTION_REQUEST_EventPackage(action, direction);
		else if (action == Action_type::Move && direction != Direction_type::None)
			ev_pack = new ACTION_REQUEST_EventPackage(action, direction);
	}

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

/******************************************
***************active_blocking_timers************
*******************************************
*Function used from the FSM to active a blocking timer when an action is checked as valid
*
*	INPUT:
*		1) Blocking_timer_type timer - The timer to be active
*	OUTPUT:
*		void.
*/
void LogicEventGenerator::active_blocking_timers(Blocking_timer_type timer) {

	switch (timer)
	{
	case Blocking_timer_type::Walking:
		al_start_timer(blocking_movements_events_timer);
		this->blocked_movements = true;
		break;

	case Blocking_timer_type::Jumping:
		al_start_timer(blocking_movements_events_timer);
		this->blocked_movements = true;
		break;

	case Blocking_timer_type::Attacking:
		al_start_timer(blocking_attacks_events_timer);
		this->blocked_attacks = true;
		break;

	default:
		break;
	}
}


/******************************************
***************turn_off_blocking_timers************
*******************************************
*Function used from the FSM to turn off a blocking timer
*
*	INPUT:
*		void.
*	OUTPUT:
*		void.
*/
void LogicEventGenerator::turn_off_blocking_timers(Blocking_timer_type timer) {


	switch (timer)
	{
	case Blocking_timer_type::Walking:
		al_stop_timer(blocking_movements_events_timer);
		this->blocked_movements = false;
		break;

	case Blocking_timer_type::Jumping:
		al_stop_timer(blocking_movements_events_timer);
		this->blocked_movements = false;
		break;

	case Blocking_timer_type::Attacking:
		al_stop_timer(blocking_attacks_events_timer);
		this->blocked_attacks = false;
		break;

	default:
		break;
	}
}

void LogicEventGenerator::flush_all_queues() {

	al_flush_event_queue(al_key_queue);
	al_flush_event_queue(al_key_timers_queue);

}



