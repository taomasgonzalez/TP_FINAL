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

	virtual void die();
	bool is_dead();

	States current_state;
	void append_action_to_character(Action_info action);
	EventHandler * ev_handler = NULL;

protected:
	bool dead = false;


};

