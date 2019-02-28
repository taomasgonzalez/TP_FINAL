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

	FSM* get_my_fsm();
	EventGenerator* get_my_ev_gen();
protected:
	bool dead = false;
	EventHandler * ev_handler = NULL;


};

