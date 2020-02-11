#pragma once
#include "Player.h"
#include "CharacterActionsFSM.h"

#define RESPAWN_TIME 3
#define INMUNE_TIME 5


class PlayerActionsFSM : public CharacterActionsFSM
{
public:
	PlayerActionsFSM(Player* player);
	~PlayerActionsFSM();
	void run_fsm(EventPackage * ev_pack);

	void update_from_allegro_timers_for_player();
	void stop_inmunity();



	struct observer_playerFSM_related {
		bool finished_pushing = false;
	};

	observer_playerFSM_related answers_4_observable;

	void revive_player();
	void start_pushing();
	void kill_player();

protected:
	void set_states();
	void create_all_timers();
	void set_processes();

private:
	std::vector<edge_t>* pushing_state = NULL;


	ALLEGRO_TIMER * respawn_timer = NULL;
	ALLEGRO_TIMER * inmune_timer = NULL;

	ALLEGRO_EVENT_QUEUE* player_ev_queue = NULL;

	Player* player = NULL;

	process_t pushing_left_process;
	process_t pushing_right_process;

};

