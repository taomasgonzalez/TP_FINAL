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


	void got_hit();
	void start_got_hit();

protected:
	void start_freezing_timer();
	void start_frozen_timer();

	ALLEGRO_TIMER* frozen_timer = NULL;
	ALLEGRO_TIMER* freezing_timer = NULL;

	std::vector<std::pair<Direction_type, double>> freezing_process;
	std::vector<std::pair<Direction_type, double>> frozen_processs;

private:
	void set_states();
	void set_processes();
	void create_all_timers();

	Enemy * enemy = NULL;
};

