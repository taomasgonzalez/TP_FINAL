#pragma once
#include "Proyectile.h"

class Snowball: public Proyectile
{
public:
	Snowball();
	~Snowball();

private:
	static double moving_speed;	//in miliseconds	
	static int life_of_use; //in number of squares visited.
};

