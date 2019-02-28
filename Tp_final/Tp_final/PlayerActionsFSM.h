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

private:
	std::vector<edge_t>* pushing_state = NULL;

	Player* player = NULL;
};

