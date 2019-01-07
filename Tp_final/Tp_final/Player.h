#pragma once
#include "Character.h"
class Player: public Character
{
public:
	Player();
	~Player();

	unsigned int lives;
	//unsigned int potion
	
	void move();
	void attack();
	void lose_life();
	void die();

};

