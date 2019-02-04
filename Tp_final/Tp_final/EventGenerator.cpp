#include "EventGenerator.h"
#include "EventPackage.h"
#include "Package.h"
#include "FSM_Class.h"
#include "Scene.h"


EventGenerator::EventGenerator(Allegro * al, Userdata* data)
{
	std::vector<std::vector<EventPackage*>> event_queues = std::vector<std::vector<EventPackage*>>();

}


EventGenerator::~EventGenerator()
{
}

void EventGenerator::empty_all_queues() {
	for (std::vector<std::queue<EventPackage*>>::iterator it = event_queues.begin(); it != event_queues.end(); ++it) 
		while ((*it).size() >= 1)
			(*it).pop();
}

void EventGenerator::append_all_queues(int total_number_of_queues)
{
	for(int i =0; i < total_number_of_queues; i++)
		event_queues.push_back(std::vector<std::queue<EventPackage*>>());
}



EventPackage * EventGenerator::fetch_event()
{
	static int actual_queue = 0;
	EventPackage * returned_package = NULL;

	if (event_queues.size() > 0) {
		returned_package = (event_queues.at(actual_queue)).front();
		(event_queues.at(actual_queue)).pop();

		actual_queue++;
		if (actual_queue >= event_queues.size())
			actual_queue = 0;
	}
	if(returned_package == NULL)
		returned_package = new NO_EVENT_EventPackage();

	return returned_package;
}

EventPackage * EventGenerator::fetch_event_soft() {

	EventPackage * new_events=NULL;
	
	if (this->soft_queue->size() >= 1) {
		new_events = this->soft_queue->front();
		this->soft_queue->pop();
	}
	else
		new_events = new NO_EVENT_EventPackage(); //no hay ningun evento para extraer entonces se manda un NO_EVENT_EventPackage

	return new_events;
	
}

EventPackage * EventGenerator::fetch_event_al(bool is_client) {

	ALLEGRO_EVENT * allegroEvent = NULL;
	EventPackage * ev_pack=NULL;

	if (al_get_next_event(al_queue, allegroEvent)) {			//tomo de la cola en caso de que no este vacia

		if (allegroEvent->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//debo quittear porque mandaron a cerrar la pantalla
			ev_pack = new LOCAL_QUIT_EventPackage();
		}
		else if (allegroEvent->type == ALLEGRO_EVENT_KEY_DOWN) {					//tecla presionada
			if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_UP) {

				if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_LEFT)

					if(is_client)
						ev_pack = new MOVE_EventPackage(Direction_type::Jump_Left);
					else
						ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Move,Direction_type::Jump_Left);

				else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_RIGHT)

					if (is_client)
						ev_pack = new MOVE_EventPackage(Direction_type::Jump_Right);
					else
						ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Move, Direction_type::Jump_Right);
				else

					if(is_client)
						ev_pack = new MOVE_EventPackage(Direction_type::Jump_Straight);
					else
						ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Move, Direction_type::Jump_Straight);
			}

			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_LEFT) {	//tecla izquierda

				if(is_client)
					ev_pack = new MOVE_EventPackage(Direction_type::Left);
				else
					ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Move, Direction_type::Left);
			}

			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//tecla derecha

				if (is_client)
					ev_pack = new MOVE_EventPackage(Direction_type::Right);
				else
					ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Move, Direction_type::Right);
			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_SPACE) {
				
				if (is_client)
					ev_pack = new ATTACK_EventPackage();
				else
					ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Attack, Direction_type::None);

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

	return ev_pack;
}


void EventGenerator::append_new_event(EventPackage * ev_pack, int queue_id)
{
	(event_queues.at(queue_id)).push(ev_pack);
}
