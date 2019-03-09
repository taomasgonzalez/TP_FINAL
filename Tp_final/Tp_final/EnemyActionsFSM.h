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

	ALLEGRO_TIMER* get_frozen_timer();
	ALLEGRO_TIMER* get_freezing_timer();

	void got_hit();
	void start_got_hit();

protected:
	void start_freezing_timer();
	void start_frozen_timer();

	ALLEGRO_TIMER* frozen_timer = NULL;
	ALLEGRO_TIMER* freezing_timer = NULL;

	std::vector<edge_t>* freezing_state = NULL;
	std::vector<edge_t>* frozen_state = NULL;

	process_t freezing_process;
	process_t frozen_processs;

	void set_states();
	void set_processes();
	void create_all_timers();

private:

	Enemy * enemy = NULL;
};

