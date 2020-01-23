#pragma once
#include "MapThing.h"
#include "EventHandler.h"


class Character: public MapThing
{
public:
	Character(unsigned int id, Sense_type sense);
	~Character();

	virtual void die();
	bool is_dead();
	bool is_moving();
	bool is_iddle();
	bool waiting_for_next_move();
	bool is_attacking();

	bool has_to_fall();
	void dont_fall();

	void append_action_to_character(Action_info action);
	EventHandler * ev_handler = NULL;

protected:
	bool dead = false;


};

