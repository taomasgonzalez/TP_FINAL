#pragma once
#include "MapThing.h"

class Proyectile: public MapThing
{
public:
	Proyectile(unsigned int id);
	~Proyectile();

	bool is_proyectile();

	virtual bool is_snowball();
	virtual bool is_fireball();

	
};

