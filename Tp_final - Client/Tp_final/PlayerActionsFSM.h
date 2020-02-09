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

	void revive_player();
	void start_pushing();
	void kill_player();


protected:
	void set_states();
	void create_all_timers();
	void set_processes();

private:
	std::vector<edge_t>* pushing_state = NULL;

	Player* player = NULL;

	process_t pushing_left_process;
	process_t pushing_right_process;

};

