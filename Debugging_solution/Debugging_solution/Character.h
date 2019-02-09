#pragma once
#include "MapThing.h"

enum class States
{
	Moving, Frozen, Snowballed, Iddle
};


class Character: public MapThing
{
public:
	Character(unsigned int id, Sense_type sense);
	~Character();
	States current_state;
	//Observer_dibujo

	virtual void die();
	bool is_dead();


protected:
	bool dead = false;

};

