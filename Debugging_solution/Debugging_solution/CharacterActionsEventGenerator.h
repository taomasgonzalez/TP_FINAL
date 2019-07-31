#pragma once
#include "MapThingEventGenerator.h"
class CharacterActionsEventGenerator :public MapThingEventGenerator
{
public:
	CharacterActionsEventGenerator(std::vector<ALLEGRO_TIMER*> timers);
	~CharacterActionsEventGenerator();
	EventPackage * fetch_event();

	void set_walking_timer(ALLEGRO_TIMER* walking_timer);
	void set_jumping_timer(ALLEGRO_TIMER* jumping_timer);
	void set_jumping_forward_timer(ALLEGRO_TIMER* jumping_forward_timer);
	void set_falling_timer(ALLEGRO_TIMER* falling_timer);
	void set_attacking_timer(ALLEGRO_TIMER* attacking_timer);

protected:
	void update_allegro_timer_events();

	ALLEGRO_TIMER* walking_timer = NULL;
	ALLEGRO_TIMER* jumping_timer = NULL;
	ALLEGRO_TIMER* jumping_forward_timer = NULL;
	ALLEGRO_TIMER* falling_timer = NULL;
	ALLEGRO_TIMER* attacking_timer = NULL;

};

