#pragma once
#include "MapThing.h"
#include "EventHandler.h"

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

	virtual void die();
	bool is_dead();


protected:
	bool dead = false;

private: 
	EventHandler * character_handler = NULL;
};

