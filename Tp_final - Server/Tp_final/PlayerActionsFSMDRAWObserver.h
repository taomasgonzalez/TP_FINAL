#pragma once
#include "DRAW.h"
#include "Observer.h"
#include "PlayerActionsFSM.h"
#include "Player.h"
#include "CharacterActionsEventGenerator.h"

class PlayerActionsFSMDRAWObserver: public Observer
{
public:
	PlayerActionsFSMDRAWObserver(PlayerActionsFSM* fsm, CharacterActionsEventGenerator* ev_gen, Player* player);

	~PlayerActionsFSMDRAWObserver();

	void update();
private:
	PlayerActionsFSM* fsm = NULL;
	DRAW* drawer = NULL;
	Player* player = NULL;
	CharacterActionsEventGenerator* ev_gen = NULL;

	Direction get_character_graph_direction(Sense_type sense);
	Direction get_character_graph_direction(Direction_type direction);
	Sense_type dir_to_sense(Direction_type sense);
	PLAYER_STATE curr_state;
	bool first_update = true;
};

