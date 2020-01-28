#pragma once
#include "Observer.h"
#include "EventGenerator.h"
#include "DRAW.h"
#include "EnemyActionsFSM.h"
#include "Enemy.h"

class EnemyActionsFSMDRAWObserver : public Observer
{
public:
	EnemyActionsFSMDRAWObserver(EnemyActionsFSM* fsm, EventGenerator* ev_gen, Enemy* enemy);
	~EnemyActionsFSMDRAWObserver();

	void update();

private:
	EnemyActionsFSM * fsm = NULL;
	EventGenerator* ev_gen = NULL;
	Enemy* enemy = NULL;
	DRAW* drawer = NULL;

	Direction get_character_graph_direction(Direction_type direction);
	Direction get_character_graph_direction(Sense_type sense);
	Sense_type dir_to_sense(Direction_type sense);
	ENEMY_STATE curr_state;
	bool first_update = true;
};

