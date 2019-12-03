#pragma once
#include "CharacterActionsEventGenerator.h"

class EnemyActionsEventGenerator : public CharacterActionsEventGenerator
{
public:
	EnemyActionsEventGenerator(std::vector<ALLEGRO_TIMER*> timers);
	~EnemyActionsEventGenerator();

	EventPackage* fetch_event();

	void set_frozen_timer(ALLEGRO_TIMER* frozen_timer);
	void set_freezing_timer(ALLEGRO_TIMER* freezing_timer);

protected:
	void update_allegro_timer_events();

	ALLEGRO_TIMER* frozen_timer = NULL;
	ALLEGRO_TIMER* freezing_timer = NULL;
};

