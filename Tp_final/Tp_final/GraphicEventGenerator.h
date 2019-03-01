#pragma once
#include "EventGenerator.h"
#include "AllegroClass.h"

class GraphicEventGenerator: public EventGenerator{
public:
	GraphicEventGenerator();

	~GraphicEventGenerator();
	EventPackage * fetch_event();

private:
	void update_allegro_timer_events();
	ALLEGRO_TIMER * fps_timer;
	ALLEGRO_EVENT_QUEUE * drawing_event_queue;
};

