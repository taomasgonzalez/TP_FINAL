#include "EventPackage.h"
#include "Package.h"
#include "FSM_Class.h"
#include "Scene.h"

unsigned int EventGenerator::time_out_count; //???

EventGenerator::EventGenerator(Allegro * al)
{
	check_for_new_messages = false;

	this->al_queue = al->get_al_queue(); 
	this->soft_queue = new std::queue<EventPackage*>();
	this->net_queue = new std::queue<EventPackage*>();
	this->time_out_timer = al->get_front_time_out_timer();
	this->time_out_count = 0;
}


EventGenerator::~EventGenerator()
{
}

void EventGenerator::append_new_net_event(EventPackage* new_ev_pack) {
	net_queue->push(new_ev_pack);
}
void EventGenerator::append_new_soft_event(EventPackage* new_ev_pack) {
	soft_queue->push(new_ev_pack);
}

EventPackage EventGenerator::fetch_event_net() {

	EventPackage new_events;

	if (this->net_queue->size() >= 1) {
		 new_events = *this->net_queue->front();
		 this->net_queue->pop();
	}
	return new_events;

}

EventPackage EventGenerator::fetch_event_soft() {
	EventPackage new_events;
	
	if (this->soft_queue->size() >= 1) {
		 new_events = *this->soft_queue->front();
		 this->soft_queue->pop();
	}
	return new_events;
	
}

EventPackage EventGenerator::fetch_event_al() {

	ALLEGRO_EVENT allegroEvent;
	EventPackage ev_pack;

	if (al_get_next_event(al_queue, &allegroEvent)) {			//tomo de la cola en caso de que no este vacia

		if (allegroEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//debo quittear porque mandaron a cerrar la pantalla
			ev_pack.ev = Event_type::LOCAL_QUIT;
		}
		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_DOWN) {					//tecla presionada
			if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_UP) {		//tecla saltar
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.my_info->action = Action_type::Move;
				ev_pack.dir = Direction::Jump;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_LEFT) {	//tecla izquierda
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.my_info->action = Action_type::Move;
				ev_pack.dir = Direction::Left;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//tecla derecha
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.my_info->action = Action_type::Move;
				ev_pack.dir = Direction::Right;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_SPACE) {
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.my_info->action = Action_type::Attack;

			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_Q){
				ev_pack.ev = Event_type::LOCAL_QUIT;
			}

		}

		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_UP) {					//no estaría levantando doble, cuando presiono y cuando suelto???
			if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_LEFT) {		//solte la izquierda
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.dir = Direction::Left;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//solte la derecha
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
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
		ev_pack.ev = Event_type::NO_EVENT;			//no hubo evento

	return ev_pack;
}



bool  EventGenerator::get_should_check_for_new_messages(void) {
	return check_for_new_messages;
}

void EventGenerator::set_should_check_for_new_messages(bool should_check) {

	check_for_new_messages = should_check;
}

