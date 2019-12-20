#pragma once
#include "MapthingEventGenerator.h"
#include "AllegroClass.h"
class ProyectilesActionsEventGenerator : public MapThingEventGenerator
{
public:
	ProyectilesActionsEventGenerator();
	~ProyectilesActionsEventGenerator();

	EventPackage * fetch_event();

	void set_moving_timer(ALLEGRO_TIMER* moving_timer);
	void set_falling_timer(ALLEGRO_TIMER* falling_timer);
	void set_impacting_timer(ALLEGRO_TIMER* impacting_timer);

protected:
	void update_allegro_timer_events();

	ALLEGRO_TIMER* moving_timer = NULL;
	ALLEGRO_TIMER* falling_timer = NULL;
	ALLEGRO_TIMER* impacting_timer = NULL;
};

