#pragma once
#include "CharacterActionsFSM.h"
#include "Enemy.h"

class EnemyActionsFSM : public CharacterActionsFSM
{
public:
	EnemyActionsFSM(Enemy* enemy);
	~EnemyActionsFSM();

	//struct observer_enemyFSM_related {

	//};
	//observer_enemyFSM_related questions_4_observer;
	//observer_enemyFSM_related answers_4_observer;
private:
	Enemy* enemy = NULL;

};

