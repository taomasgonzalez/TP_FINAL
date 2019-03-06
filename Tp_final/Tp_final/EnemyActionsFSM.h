#pragma once
#include "CharacterActionsFSM.h"
#include "Enemy.h"

class EnemyActionsFSM : public CharacterActionsFSM
{
public:
	EnemyActionsFSM(Enemy* enemy);
	~EnemyActionsFSM();

	std::vector<ALLEGRO_TIMER*> get_all_my_timers();

	//struct observer_enemyFSM_related {
	//};
	//observer_enemyFSM_related questions_4_observer;
	//observer_enemyFSM_related answers_4_observer;
	std::vector<edge_t>* freezing_state = NULL;
	std::vector<edge_t>* frozen_state = NULL;
};

