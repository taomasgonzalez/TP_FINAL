#pragma once
#include "Enemy.h"
class GreenFatty: public Enemy
{
public:
	GreenFatty();
	~GreenFatty();

private:
	static double moving_speed;	//in miliseconds		
};

