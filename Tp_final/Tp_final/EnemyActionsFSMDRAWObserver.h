#pragma once
#include "Observer.h"
#include "DRAW.h"
#include "EnemyActionsFSM.h"
#include "Enemy.h"

class EnemyActionsFSMDRAWObserver : public Observer
{
public:
	EnemyActionsFSMDRAWObserver(EnemyActionsFSM* fsm, Enemy* enemy);
	~EnemyActionsFSMDRAWObserver();

	void update();
private:
	EnemyActionsFSM * fsm = NULL;
	Enemy* enemy = NULL;
	DRAW* drawer = NULL;
};

