#pragma once
#include "Character.h"

class Enemy: public Character
{
public:
	Enemy(unsigned int id);
	~Enemy();

	unsigned int amount_of_hits_taken;
	
	bool is_enemy();
	void act();
	void unfreeze();
	void be_hit();
	
private:
	//frozen_timer;
	void freeze();
};

