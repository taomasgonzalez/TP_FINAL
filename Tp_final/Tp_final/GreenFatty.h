#pragma once
#include "Enemy.h"
class GreenFatty: public Enemy
{
public:
	GreenFatty(unsigned int id);
	~GreenFatty();
	void act();
private:
	static double moving_speed;	//in miliseconds		

};

