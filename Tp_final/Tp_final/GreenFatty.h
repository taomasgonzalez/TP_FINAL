#pragma once
#include "Enemy.h"
class GreenFatty: public Enemy
{
public:
	GreenFatty(unsigned int id);
	~GreenFatty();
	Action_info* act();
private:
	static double moving_speed;	//in miliseconds		
	void shoot_fireball(Action_info * next_enemy_action);
};

