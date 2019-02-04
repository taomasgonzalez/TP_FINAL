#pragma once
#include "EventGenerator.h"


class LogicEventGenerator : public EventGenerator
{
	
public:
	enum class Queues { allegro, net, soft, TOTAL_QUEUES };

	LogicEventGenerator(Allegro * al, Userdata* data);
	~LogicEventGenerator();

	friend class CommunicationEventsObserver;
	friend class ScenarioEventsObserver;
	friend class FSMEventsObserver;

	EventPackage* fetch_event();
	void empty_all_queues();

private:
	ALLEGRO_EVENT_QUEUE * al_queue;

	Userdata * my_user_data; //PQ tienne este puntero? lo necesita realmente?
	ALLEGRO_TIMER * time_out_timer;  // has to be moved to allegro.cpp??

	unsigned int time_out_count;
	void update_from_allegro_events();

};


/*
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


	}

		else
			ev_pack = new NO_EVENT_EventPackage();

	return ev_pack;
}
*/