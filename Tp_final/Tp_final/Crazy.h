#pragma once
#include "Enemy.h"

class Crazy: public Enemy
{
public:
	Crazy(unsigned int id);
	~Crazy();

	Action_info act();
private:
	static double moving_speed;	//in miliseconds	

};

