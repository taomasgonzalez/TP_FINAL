#pragma once
#include "Player.h"
#include "CharacterActionsFSM.h"

class PlayerActionsFSM : public CharacterActionsFSM
{
public:
	PlayerActionsFSM(Player* player);
	~PlayerActionsFSM();

	struct observer_playerFSM_related {
		bool finished_pushing = false;
	};

	observer_playerFSM_related answers_4_observable;

	void start_pushing_timer();
	void revive_player();
	std::vector<ALLEGRO_TIMER*> get_all_my_timers();

private:
	std::vector<edge_t>* pushing_state = NULL;

	ALLEGRO_TIMER* pushing_timer = NULL;
	Player* player = NULL;

	process_t pushing_left_proccess;
	process_t pushing_right_proccess;

	void set_states();
	void create_all_timers();
	void set_processes();
};

