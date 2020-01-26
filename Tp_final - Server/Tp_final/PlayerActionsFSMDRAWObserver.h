#pragma once
#include "DRAW.h"
#include "Observer.h"
#include "PlayerActionsFSM.h"
#include "Player.h"
#include "EventGenerator.h"

class PlayerActionsFSMDRAWObserver: public Observer
{
public:
	PlayerActionsFSMDRAWObserver(PlayerActionsFSM* fsm, EventGenerator* ev_gen, Player* playe);

	~PlayerActionsFSMDRAWObserver();

	void update();
private:
	PlayerActionsFSM* fsm = NULL;
	DRAW* drawer = NULL;
	Player* player = NULL;
	EventGenerator* ev_gen = NULL;



	Direction get_character_graph_direction(Sense_type sense);
	Direction get_character_graph_direction(Direction_type direction);
	Sense_type dir_to_sense(Direction_type sense);
	PLAYER_STATE curr_state;
	bool first_update = true;
};

