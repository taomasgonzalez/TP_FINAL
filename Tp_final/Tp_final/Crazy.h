#pragma once
#include "Enemy.h"
class Crazy: public Enemy
{
public:
	Crazy();
	~Crazy();

private:
	static double moving_speed;	//in miliseconds	
};

