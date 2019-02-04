#pragma once
#include "Enemy.h"

class PurpleGuy: public Enemy
{
public:
	PurpleGuy(unsigned int id);
	~PurpleGuy();

	EA_info act();

private:
	static double moving_speed;	//in miliseconds	

};

