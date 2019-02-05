#pragma once
#include "Character.h"
#include "AllegroClass.h"
#include <iostream>
#include <chrono>
#include <random>

class Enemy: public Character
{
public:
	Enemy(unsigned int id);
	~Enemy();

	unsigned int amount_of_hits_taken;

	bool is_enemy();
	virtual EA_info act() = 0;
	virtual void unfreeze();
	virtual void be_hit();


	ALLEGRO_TIMER * get_acting_timer();
	

protected:
	//frozen_timer;
	void freeze();

	ALLEGRO_TIMER * acting_timer;

	static std::uniform_real_distribution<double> acting_probabilities;
	static unsigned seed;
	static std::default_random_engine generator;
	
	void move_in_same_direction(EA_info* next_enemy_action);
	void move_in_opposite_direction(EA_info* next_enemy_action);
	void stay_still(EA_info * next_enemy_action);
	void jump(EA_info * next_enemy_action);

};

