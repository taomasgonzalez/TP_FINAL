#pragma once
#include "Enemy.h"

class PurpleGuy: public Enemy
{
public:
	PurpleGuy(unsigned int id);
	~PurpleGuy();

	Action_info act();

	bool calculate_shortest_distance = false;
	void set_next_movement_2_nearest_player(Position final_pos);

private:
	static double moving_speed;	//in miliseconds	
	void move_to_nearest_player(Action_info * next_enemy_action);
	Position next_movement_2_nearest_player;
};

