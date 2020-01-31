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
	bool is_falling();
	virtual bool is_iddle();
	virtual bool is_walking();

	bool is_attacking();
	Direction_type in_wich_direction_is_the_character_walking();


	bool has_to_fall();
	void dont_fall();

	bool waiting_for_next_move();


	void append_action_to_character(Action_info action);
	EventHandler * ev_handler = NULL;

protected:
	bool dead = false;


};

