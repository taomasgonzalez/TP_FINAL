#include "EventGenerator.h"
#include "Package.h"
#include "FSM_Class.h"
#include "Scene.h"

unsigned int EventGenerator::time_out_count;
EventGenerator::EventGenerator(Allegro * al)
{
	check_for_new_messages = false;

	this->al_queue = al->get_al_queue(); 
	this->soft_queue = new std::queue<EventPackage*>();
	this->net_queue = new std::queue<EventPackage*>();
	this->time_out_timer = al->get_time_out_timer();
	this->time_out_count = 0;
}


EventGenerator::~EventGenerator()
{
}

EventPackage EventGenerator::fetch_event_net() {

	EventPackage new_events;

	if (net_queue->size >= 1) {
		EventPackage new_events = *net_queue->front();
		net_queue->pop();
	}
	return new_events;

}

EventPackage EventGenerator::fetch_event_soft() {
	EventPackage new_events;
	
	if (soft_queue->size >= 1) {
		EventPackage new_events = *soft_queue->front();
		soft_queue->pop();
	}
	return new_events;
	
}

EventPackage EventGenerator::fetch_event_al() {

	ALLEGRO_EVENT allegroEvent;
	EventPackage ev_pack;

	if (al_get_next_event(al_queue, &allegroEvent)) {			//tomo de la cola en caso de que no este vacia

		if (allegroEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//debo quittear porque mandaron a cerrar la pantalla
			ev_pack.ev = Event::LOCAL_QUIT;
		}
		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_DOWN) {					//tecla presionada
			if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_UP) {		//tecla saltar
				ev_pack.ev = Event::LOCAL_ACTION;
				ev_pack.act = Action::Move;
				ev_pack.dir = Direction::Jump;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_LEFT) {	//tecla izquierda
				ev_pack.ev = Event::LOCAL_ACTION;
				ev_pack.act = Action::Move;
				ev_pack.dir = Direction::Left;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//tecla derecha
				ev_pack.ev = Event::LOCAL_ACTION;
				ev_pack.act = Action::Move;
				ev_pack.dir = Direction::Right;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_SPACE) {
				ev_pack.ev = Event::LOCAL_ACTION;
				ev_pack.act = Action::Attack;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_Q){
				ev_pack.ev = Event::LOCAL_QUIT;
			}

		}

		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_UP) {					//tecla soltada
			if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_LEFT) {		//solte la izquierda
				ev_pack.ev = Event::LOCAL_ACTION;
				ev_pack.dir = Direction::Left;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//solte la derecha
				ev_pack.ev = Event::LOCAL_ACTION;
				ev_pack.dir = Direction::Right;
			}
		}
		else if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
			//if () {
			//	ev_pack.ev = Event::LOCAL_ERROR;
			//}
		}
	}
	else
		ev_pack.ev = Event::NO_EVENT;			//no hubo evento

	return ev_pack;
}



bool  EventGenerator::get_should_check_for_new_messages(void) {
	return check_for_new_messages;
}

void EventGenerator::set_should_check_for_new_messages(bool should_check) {
	check_for_new_messages = should_check;
}