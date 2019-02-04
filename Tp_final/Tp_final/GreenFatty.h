#pragma once
#include "Enemy.h"
class GreenFatty: public Enemy
{
public:
	GreenFatty(unsigned int id);
	~GreenFatty();
	EA_info act();
private:
	static double moving_speed;	//in miliseconds		

};

