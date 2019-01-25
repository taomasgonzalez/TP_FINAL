#include "EventGenerator.h"
#include "EventPackage.h"
#include "Package.h"
#include "FSM_Class.h"
#include "Scene.h"


EventGenerator::EventGenerator(Allegro * al, FSM * fsm, Userdata* data)
{

	this->al_queue = al->get_al_queue(); 
	this->soft_queue = new std::queue<EventPackage*>();
	this->net_queue = new std::queue<EventPackage*>();
	this->time_out_timer = al->get_front_time_out_timer();
	this->time_out_count = 0;
	this->my_fsm = fsm;
	this->my_user_data = data;

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
void EventGenerator::append_new_allegro_event(EventPackage* new_ev_pack) {
	allegro_queue->push(new_ev_pack);
}

EventPackage* EventGenerator::fetch_event_net() {

	EventPackage * new_events=NULL;

	if (this->net_queue->size() >= 1) {
		 new_events = this->net_queue->front();
		 this->net_queue->pop();
	}
	else
		new_events = new NO_EVENT_EventPackage(true); //no hay ningun evento para extraer entonces se manda un NO_EVENT_EventPackage

	return new_events;

}

EventPackage * EventGenerator::fetch_event_soft() {

	EventPackage * new_events=NULL;
	
	if (this->soft_queue->size() >= 1) {
		new_events = this->soft_queue->front();
		this->soft_queue->pop();
	}
	else
		new_events = new NO_EVENT_EventPackage(true); //no hay ningun evento para extraer entonces se manda un NO_EVENT_EventPackage

	return new_events;
	
}

EventPackage * EventGenerator::fetch_event_al() {

	EventPackage * new_events = NULL;

	if (this->allegro_queue->size() >= 1) {
		new_events = this->allegro_queue->front();
		this->allegro_queue->pop();
	}
	return new_events;

/*		LOGICA TIENE QUE IR AL HACER UN EVENTO DE ALLEGRO, ANALISIS PREVIO ANTES TE METERLO A UNA COLA
	
	ALLEGRO_EVENT * allegroEvent=NULL;
	EventPackage * ev_pack;

	if (al_get_next_event(al_queue, allegroEvent)) {			//tomo de la cola en caso de que no este vacia

		if (allegroEvent->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//debo quittear porque mandaron a cerrar la pantalla
			ev_pack = new QUIT_EventPackage(true); 
		}
		else if (allegroEvent->type == ALLEGRO_EVENT_KEY_DOWN) {					//tecla presionada
			if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_UP) {		//tecla saltar
				
				ev_pack=new MOVE_EventPackage(true,)
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.my_info->action = Action_type::Move;
				ev_pack.dir = Direction_type::Jump;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_LEFT) {	//tecla izquierda
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.my_info->action = Action_type::Move;
				ev_pack.dir = Direction_type::Left;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//tecla derecha
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.my_info->action = Action_type::Move;
				ev_pack.dir = Direction_type::Right;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_SPACE) {
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.my_info->action = Action_type::Attack;

			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_Q){
				ev_pack = new QUIT_EventPackage(true);

			}

		}

		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_UP) {					//no estaría levantando doble, cuando presiono y cuando suelto???
			if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_LEFT) {		//solte la izquierda
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.dir = Direction_type::Left;
			}
			else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//solte la derecha
				ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
				ev_pack.dir = Direction_type::Right;
			}
		}
		else if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
			//if () {
			//	ev_pack.ev = My_Event::LOCAL_ERROR;
			//}
		}
	}
	else
		ev_pack.ev = Event_type::NO_EVENT;			//no hubo evento

	return ev_pack;
*/


}




