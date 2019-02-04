#pragma once
#include "MapThing.h"

class Proyectile: public MapThing
{
public:
	Proyectile(unsigned int id, Sense_type proyectile_sense);
	~Proyectile();

	bool is_proyectile();

	virtual bool is_snowball();
	virtual bool is_fireball();

};

