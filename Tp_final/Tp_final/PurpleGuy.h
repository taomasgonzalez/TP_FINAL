#pragma once
#include "Enemy.h"

class PurpleGuy: public Enemy
{
public:
	PurpleGuy(unsigned int id);
	~PurpleGuy();
private:
	static double moving_speed;	//in miliseconds	
};

