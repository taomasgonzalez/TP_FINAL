#pragma once
#include "Enemy.h"

class PurpleGuy: public Enemy
{
public:
	PurpleGuy(unsigned int id, Sense_type sense);
	~PurpleGuy();

	Action_info act();

	void set_next_movement_2_nearest_player(Position final_pos);

	struct purple_obs_info{
		bool calculate_shortest_distance = false;
	};
	purple_obs_info purple_questions_4_observer;
	purple_obs_info purple_answers_4_observable;

private:
	static double moving_speed;	//in miliseconds	
	void move_to_nearest_player(Action_info * next_enemy_action);
	Position next_movement_2_nearest_player;
};

