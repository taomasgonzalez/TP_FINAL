#include "EventGenerator.h"
#include "EventPackage.h"
#include "Package.h"
#include "FSM_Class.h"
#include "Scene.h"


EventGenerator::EventGenerator(Allegro * al, Userdata* data)
{

	this->al_queue = al->get_al_queue(); 
	this->soft_queue = new std::queue<EventPackage*>();
	this->net_queue = new std::queue<EventPackage*>();
	this->allegro_queue = new std::queue<EventPackage*>(); ///para debbugear tommy, no me fajes

	this->time_out_timer = al->get_front_time_out_timer();
	this->time_out_count = 0;
	this->my_user_data = data;

}


EventGenerator::~EventGenerator()
{
}

void EventGenerator::empty_all_queues() {

	while (this->net_queue->size() >= 1) 
	{
		this->net_queue->pop();
	}

	while (this->soft_queue->size() >= 1)
	{
		this->soft_queue->pop();
	}

	al_flush_event_queue(al_queue);
}

void EventGenerator::append_new_net_event(EventPackage* new_ev_pack) {
	net_queue->push(new_ev_pack);
}
void EventGenerator::append_new_soft_event(EventPackage* new_ev_pack) {
	soft_queue->push(new_ev_pack);
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
	else
		new_events = new NO_EVENT_EventPackage(true); //no hay ningun evento para extraer entonces se manda un NO_EVENT_EventPackage

	return new_events;
}

//		IMPORTANTE:COMO LOS LEVANTAS DIRACTAMENTE DE ALLEGRO QUEUE ESTOS MOVIMEINTOS PUEDEN NO SER VALIDOS POR
//		IRSE DEL MAPA POR EJMPLO, Y SE MANDAN DIRECTAMENTE A LA FSM SIN ANALIZAR, SE PUEDE LLAMAR A LA FUNCIÓN
//	    Scene::is_the_action_possible(EventPackage* package_to_be_analyze)  como en ScenarioEventsObserver::update()

	
/*	ALLEGRO_EVENT * allegroEvent=NULL;
	EventPackage * ev_pack;

	if (al_get_next_event(al_queue, allegroEvent)) {			//tomo de la cola en caso de que no este vacia

		if (allegroEvent->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//debo quittear porque mandaron a cerrar la pantalla
			ev_pack = new QUIT_EventPackage(true); 
		}
		else if (allegroEvent->type == ALLEGRO_EVENT_KEY_DOWN) {					//tecla presionada
			if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_UP) {		//tecla saltar
				
				//ev_pack=new MOVE_EventPackage(true, ) mi jugador esta en scenario(Scene::give_me_my_player();), hay que buscar la otra info también en scene imagino

			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_LEFT) {	//tecla izquierda
				//ev_pack=new MOVE_EventPackage(true, ) mi jugador esta en scenario, hay que buscar la otra info también en scene imagino

			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//tecla derecha
				//ev_pack=new MOVE_EventPackage(true, ) mi jugador esta en scenario, hay que buscar la otra info también en scene imagino

			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_SPACE) {
				//ev_pack=new ATTACK_EventPackage(true, ) mi jugador esta en scenario, hay que buscar la otra info también en scene imagino


			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_Q){
				ev_pack = new QUIT_EventPackage(true);

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
	else
		ev_pack = new NO_EVENT_EventPackage(true);
		

	return ev_pack;



}
*/


