#pragma once
#include "CharacterActionsFSM.h"
#include "Allegroclass.h"
#include "Enemy.h"


class EnemyActionsFSM : public CharacterActionsFSM
{
public:
	EnemyActionsFSM(Enemy* enemy);
	~EnemyActionsFSM();

	void run_fsm(EventPackage * ev_pack);
	void update_from_allegro_timers_for_enemy();



	struct Enemyobserver_info {
		bool start_freezing_state1_graph = false;
		bool start_freezing_state2_graph = false;
		bool start_freezing_state3_graph = false;
		bool start_fozen_graph = false;
		bool start_ballCharging_graph = false;
		bool start_ballPushing_graph = false;
		bool start_ballexplotion_graph = false;
	};

	Enemyobserver_info enemyObs_info;

	ALLEGRO_TIMER* get_frozen_timer();
	ALLEGRO_TIMER* get_freezing_timer();

	void got_hit();
	void start_got_hit();
	void partially_unfroze();
	void unfroze();
	void unfreeze();
	void froze();
	void start_moving_snowball();

protected:
	void start_freezing_timer();
	void start_frozen_timer();


	std::vector<edge_t>* freezing_state = NULL;
	std::vector<edge_t>* frozen_state = NULL;

	process_t freezing_process;
	process_t frozen_processs;

	void set_states();
	void set_processes();
	void create_all_timers();

private:

	process_t rolling_left_process;
	process_t rolling_right_process;

	ALLEGRO_TIMER* frozen_timer = NULL;
	ALLEGRO_TIMER* freezing_timer = NULL;

	ALLEGRO_EVENT_QUEUE* defrost_queue = 0;	//will get events from the timers of the enemies

	void handle_hits(void);

	Enemy * enemy = NULL;
};

