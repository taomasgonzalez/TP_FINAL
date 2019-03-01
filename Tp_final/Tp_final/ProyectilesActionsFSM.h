#pragma once
#include "FSM_Class.h"
#include "AllegroClass.h"
#include "Proyectile.h"

class ProyectilesActionsFSM : public FSM
{
public:
	ProyectilesActionsFSM(Proyectile* proyectile);
	~ProyectilesActionsFSM();

	struct obs_info{
		bool move = false;
		bool impact = false;
		bool fall = false;
	};

	obs_info observer_info;

	Direction_type get_direction();
	void impact();
	void start_moving();
	void start_falling();
protected:

	std::vector<edge_t>* moving_state = NULL;
	std::vector<edge_t>* impact_state = NULL;
	std::vector<edge_t>* inactive_state = NULL;
	std::vector<edge_t>* falling_state = NULL;
	Direction_type direction;

	ALLEGRO_TIMER* moving_timer = NULL;
	ALLEGRO_TIMER* falling_timer = NULL;
	
};

