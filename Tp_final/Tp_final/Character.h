#pragma once
#include "MapThing.h"

enum class States
{
	Moving, Frozen
};

class Character: public MapThing
{
public:
	Character(unsigned int id);
	~Character();
	States current_state;
	//Observer_dibujo

	virtual void die();
	bool is_dead();

protected:
	bool dead = false;
};

