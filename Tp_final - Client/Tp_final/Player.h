#pragma once
#include "Character.h"
#include "EventHandler.h"

class Player : public Character
{
public:
	Player(unsigned int id, bool is_nick, Sense_type sense);
	~Player();

	unsigned int lives = 3;

	bool is_player();
	void move();
	void attack();
	void die();
	void revive();
	bool has_lives();

	bool is_inmune();
	void set_the_player_inmunity(bool is_inmuned);

private:

	bool being_inmuned = false;

	void lose_life();
	bool run_out_of_lives = false;
};

