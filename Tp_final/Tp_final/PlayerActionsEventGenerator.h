#pragma once
#include "CharacterActionsEventGenerator.h"

class PlayerActionsEventGenerator : public CharacterActionsEventGenerator
{
public:
	PlayerActionsEventGenerator(std::vector<ALLEGRO_TIMER*> timers);
	~PlayerActionsEventGenerator();

	EventPackage* fetch_event();
	void set_pushing_timer(ALLEGRO_TIMER* pushing_timer);

protected:
	void update_allegro_timer_events();
	ALLEGRO_TIMER* pushing_timer = NULL;
};

