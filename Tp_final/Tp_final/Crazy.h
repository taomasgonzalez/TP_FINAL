#pragma once
#include "Enemy.h"

class Crazy: public Enemy
{
public:
	Crazy(unsigned int id);
	~Crazy();

	void act();
private:
	static double moving_speed;	//in miliseconds	

};

