#pragma once
#include "MapThing.h"
#include "EventHandler.h"

class Proyectile: public MapThing
{
public:
	Proyectile(unsigned int id, Sense_type proyectile_sense);
	~Proyectile();

	bool is_proyectile();

	virtual bool is_snowball();
	virtual bool is_fireball();
	ALLEGRO_TIMER * get_moving_timer();

	EventHandler * ev_handler = NULL;
protected:
	ALLEGRO_TIMER * moving_timer = NULL;
};

