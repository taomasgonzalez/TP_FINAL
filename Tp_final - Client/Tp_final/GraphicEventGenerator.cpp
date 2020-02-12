#include "GraphicEventGenerator.h"

GraphicEventGenerator::GraphicEventGenerator() : EventGenerator()
{
	drawing_event_queue = al_create_event_queue();
	fps_timer = al_create_timer(1.0/FPS);		//FPS de guido
	al_register_event_source(drawing_event_queue, al_get_timer_event_source(fps_timer));
	al_register_event_source(drawing_event_queue, al_get_keyboard_event_source());
	append_all_queues(1);
}

GraphicEventGenerator::~GraphicEventGenerator()
{

}
EventPackage * GraphicEventGenerator::fetch_event() {

	update_allegro_timer_events();
	return EventGenerator::fetch_event();
}

void GraphicEventGenerator::update_allegro_timer_events() {
	ALLEGRO_EVENT allegroEvent;
	EventPackage * ev_pack = NULL;

	if (Userdata::generating_graphic_events)
		al_start_timer(fps_timer);

	if (al_get_next_event(drawing_event_queue, &allegroEvent)) 
		if (allegroEvent.type == ALLEGRO_EVENT_TIMER){
			if (allegroEvent.timer.source == fps_timer) 
				append_new_event(new EventPackage(Event_type::FPS_TICKED,0, true), 0);
		}
		else if (allegroEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			append_new_event(new ERROR_EventPackage(true),(int) LogicQueues::allegro); //LO CAMBIE POR ERROR, porque si es LOCAL_QUIT tiene que esperar el ACK de la otra compu, y eso no nunca va a llegar porque cerraste la pantalla
		}
}

void GraphicEventGenerator::flush_all_queues() {

	al_flush_event_queue(drawing_event_queue);

}