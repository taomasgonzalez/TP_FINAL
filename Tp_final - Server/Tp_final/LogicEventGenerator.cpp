#include "LogicEventGenerator.h"
#include <iostream>


LogicEventGenerator::LogicEventGenerator(Allegro * al, Userdata* data): EventGenerator()
{
	this->my_user_data = data;
	this->al = al;
	al_key_queue = al_create_event_queue();
	al_register_event_source(al_key_queue, al_get_keyboard_event_source());
	//time_out_timer = al->get_front_time_out_timer();
	//al_register_event_source
	time_out_count = 0;
	
	coordinate_scene_events_queue = al_create_event_queue();
	coordinate_scene_events_timer = al_create_timer(50.0 / 1000.0);
	al_register_event_source(coordinate_scene_events_queue, al_get_timer_event_source(coordinate_scene_events_timer));
	//al_start_timer(coordinate_scene_events_timer);
	append_all_queues( (int) LogicQueues::TOTAL_QUEUES);
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
	update_from_allegro_keyboard_events();
	//update_from_allegro_timer_events(); la comenté porque la función no está hecha 31/7/19 Germo
}

void LogicEventGenerator::update_from_allegro_keyboard_events() {

	ALLEGRO_EVENT  allegroEvent ;
	EventPackage * ev_pack = NULL;

	if (al_get_next_event(al_key_queue, &allegroEvent)) {			//tomo de la cola en caso de que no este vacia

		if (allegroEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//debo quittear porque mandaron a cerrar la pantalla				
			ev_pack = new LOCAL_QUIT_EventPackage();
		}
		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_DOWN) {					//tecla presionada
			if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_UP) {
				jump_move_pressed = true;
				if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_LEFT)
					ev_pack = direction_to_event_package(Action_type::Move, Direction_type::Jump_Left);
				else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT)
					ev_pack = direction_to_event_package(Action_type::Move, Direction_type::Jump_Right);
				else
					ev_pack = direction_to_event_package(Action_type::Move, Direction_type::Jump_Straight);

			}

			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_LEFT) { 	//tecla izquierda
				side_move_dir = Direction_type::Left;
				ev_pack = direction_to_event_package(Action_type::Move, side_move_dir);
				side_move_pressed = true;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//tecla derecha
				side_move_dir = Direction_type::Right;
				ev_pack = direction_to_event_package(Action_type::Move, side_move_dir);
				side_move_pressed = true;
			}
			//
			//if (side_move_pressed && jump_move_pressed) {
			//	if (ev_pack != NULL)
			//		delete ev_pack;
			//	Direction_type new_dir = (side_move_dir == Direction_type::Left) ? 
			//							Direction_type::Jump_Left : 
			//							Direction_type::Jump_Right;

			//	ev_pack = direction_to_event_package(Action_type::Move, new_dir);
			//}

			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_SPACE) 
				direction_to_event_package(Action_type::Attack, Direction_type::None);

			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_Q) 
				ev_pack = new LOCAL_QUIT_EventPackage();

		}
		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_UP) {
			if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_UP)
				jump_move_pressed = false;
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_LEFT
				|| allegroEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				side_move_pressed = false;
		}
	}
	if(ev_pack != NULL)
		append_new_event(ev_pack,(int) LogicQueues::allegro);

}

EventPackage* LogicEventGenerator::direction_to_event_package(Action_type action, Direction_type dir) {
	EventPackage* ev_pack = NULL;

	if (!my_user_data->my_network_data.is_client()) {
		if(action == Action_type::Attack)
			ev_pack = new ATTACK_EventPackage();
		else  if(action == Action_type::Move)
			ev_pack = new MOVE_EventPackage(dir);
	}
	else 
		ev_pack = new ACTION_REQUEST_EventPackage(action, dir);
	
	return ev_pack;
}


void LogicEventGenerator::update_from_allegro_timer_events() {
	ALLEGRO_EVENT allegroEvent;
	EventPackage * ev_pack = NULL;

	if (al_get_next_event(coordinate_scene_events_queue, &allegroEvent)) {
		if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
			if (allegroEvent.timer.source == coordinate_scene_events_timer) {
			}
			else if (allegroEvent.timer.source == time_out_timer) {

			}
		}
	}

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
	al_flush_event_queue(coordinate_scene_events_queue);
}
