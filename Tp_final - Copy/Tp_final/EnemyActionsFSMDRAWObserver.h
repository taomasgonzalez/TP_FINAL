#pragma once
#include "Observer.h"
#include "CharacterActionsEventGenerator.h"
#include "DRAW.h"
#include "EnemyActionsFSM.h"
#include "Enemy.h"

class EnemyActionsFSMDRAWObserver : public Observer
{
public:
	EnemyActionsFSMDRAWObserver(EnemyActionsFSM* fsm, CharacterActionsEventGenerator* ev_gen, Enemy* enemy);
	~EnemyActionsFSMDRAWObserver();

	void update();

private:

	EnemyActionsFSM * fsm = NULL;
	CharacterActionsEventGenerator* ev_gen = NULL;
	Enemy* enemy = NULL;
	DRAW* drawer = NULL;

	Direction get_character_graph_direction(Sense_type sense);

	ENEMY_STATE curr_state;
};

