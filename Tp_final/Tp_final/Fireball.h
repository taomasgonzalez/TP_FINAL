#pragma once
#include "Proyectile.h"
class Fireball: public Proyectile
{
public:
	Fireball();
	~Fireball();

private:
	static double moving_speed;	//in miliseconds	
	static int life_of_use;	//in number of squares visited
};

