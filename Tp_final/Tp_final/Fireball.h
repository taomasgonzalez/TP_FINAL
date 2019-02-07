#pragma once
#include "Proyectile.h"
class Fireball: public Proyectile
{
public:
	Fireball(unsigned int id, Sense_type proyectile_sense);
	~Fireball();

	bool is_fireball();
private:
	static double moving_speed;	//in miliseconds	
	static int life_of_use;	//in number of squares visited
};

