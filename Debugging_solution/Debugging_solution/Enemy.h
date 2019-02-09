#pragma once
#include "Character.h"
#include "AllegroClass.h"
#include "Observable.h"
#include <iostream>
#include <chrono>
#include <random>
#include "Action_Info.h"

class Enemy: public Character, public Observable
{
public:
	Enemy(unsigned  int id, Sense_type sense);
	~Enemy();

	unsigned int amount_of_hits_taken;

	bool is_enemy();
	virtual Action_info act() = 0;

	//falta implementar
	virtual void unfreeze();
	//falta implementar
	virtual void be_hit();


	ALLEGRO_TIMER * get_acting_timer();
	
	struct obs_info {
		bool can_move_in_same_direction = false;
		bool can_move_in_opposite_direction = false;
		bool can_jump = false;
	};
	obs_info questions_4_observer;
	//answers should only be checked immediately after asking the according question!
	obs_info answers_4_observable;

protected:
	//frozen_timer;
	//falta implementar
	void freeze();

	ALLEGRO_TIMER * acting_timer;

	static std::uniform_real_distribution<double> acting_probabilities;
	static unsigned seed;
	static std::default_random_engine generator;

	void EA_info_common_filling(Action_info * next_enemy_action);

	bool can_move_in_same_direction();
	bool move_in_same_direction(Action_info* next_enemy_action);

	bool can_move_in_opposite_direction();
	bool move_in_opposite_direction(Action_info* next_enemy_action);

	void stay_still(Action_info * next_enemy_action);

	bool can_jump();
	bool jump(Action_info * next_enemy_action);

};

