#include "LogicEventGenerator.h"


LogicEventGenerator::LogicEventGenerator(Allegro * al, Userdata* data): EventGenerator(Allegro * al, Userdata* data)
{
	al_queue = al->get_al_queue();
	soft_queue = new std::queue<EventPackage*>();
	net_queue = new std::queue<EventPackage*>();
	allegro_queue = new std::queue<EventPackage*>();
	time_out_timer = al->get_front_time_out_timer();
	time_out_count = 0;
	
	my_user_data = data;
}


LogicEventGenerator::~LogicEventGenerator()
{
	delete allegro_queue;
	delete soft_queue;
	delete net_queue;
}

EventPackage * LogicEventGenerator::fetch_event()
{
	update_from_allegro_events();
	return EventGenerator::fetch_event();
}

void LogicEventGenerator::update_from_allegro_events() {

	ALLEGRO_EVENT * allegroEvent = NULL;
	EventPackage * ev_pack = NULL;

	if (al_get_next_event(al_queue, allegroEvent)) {			//tomo de la cola en caso de que no este vacia

		if (allegroEvent->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//debo quittear porque mandaron a cerrar la pantalla
			ev_pack = new LOCAL_QUIT_EventPackage();
		}
		else if (allegroEvent->type == ALLEGRO_EVENT_KEY_DOWN) {					//tecla presionada
			if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_UP) {

				if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_LEFT)
					ev_pack = new MOVE_EventPackage(Direction_type::Jump_Left);
				else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_RIGHT)
					ev_pack = new MOVE_EventPackage(Direction_type::Jump_Right);
				else
					ev_pack = new MOVE_EventPackage(Direction_type::Jump_Straight);
			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_LEFT) {	//tecla izquierda
				ev_pack = new MOVE_EventPackage(Direction_type::Left);

			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//tecla derecha
				ev_pack = new MOVE_EventPackage(Direction_type::Right);

			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_SPACE) {
				ev_pack = new ATTACK_EventPackage();

			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_Q) {
				ev_pack = new LOCAL_QUIT_EventPackage();
			}

		}

		/*else if (allegroEvent.type == ALLEGRO_EVENT_KEY_UP) {					//no estaría levantando doble, cuando presiono y cuando suelto??? Yo diría que si
		if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_LEFT) {		//solte la izquierda
		ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
		ev_pack.dir = Direction_type::Left;
		}
		else if (allegroEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//solte la derecha
		ev_pack.ev = Event_type::LOCAL_ACTION_ACCEPTED;
		ev_pack.dir = Direction_type::Right;
		}
		}
		else if (allegroEvent->type == ALLEGRO_EVENT_TIMER) { //?
		//if () {
		//	ev_pack.ev = My_Event::LOCAL_ERROR;
		//}
		}
		}
		}*/

	}

	else
		ev_pack = new NO_EVENT_EventPackage();

	allegro_queue->push(ev_pack);
}

void LogicEventGenerator::empty_all_queues() {
	EventGenerator::empty_all_queues();
	al_flush_event_queue(al_queue);
}

void LogicEventGenerator::append_all_queues()
{
	std::vector<std::vector<EventPackage*>*>::iterator it = event_queues.begin();
	//fijarse bien porque tal vez los inserta mal, tiene que ver con capacidad y tama;o y el orden en que inserto.
	event_queues.insert(it + LogicEventGenerator::Queues::allegro, allegro_queue);
	event_queues.insert(it + LogicEventGenerator::Queues::net, net_queue);
	event_queues.insert(it + LogicEventGenerator::Queues::soft, soft_queue);

}
