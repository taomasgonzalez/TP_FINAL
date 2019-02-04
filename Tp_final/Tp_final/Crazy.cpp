#include "Crazy.h"

double Crazy::moving_speed = 300;

Crazy::Crazy(unsigned int id): Enemy(id)
{
	printable = Item_type::CRAZY;
}


Crazy::~Crazy()
{
}

Enemy::EA_info Crazy::act() {
	al_stop_timer(acting_timer);
	double sample = acting_probabilities(generator);
	double timer_speed;

	EA_info returnable_EA;

	if (sample <= 0.75) {
		move_in_same_direction(&returnable_EA);
		//timer_speed = ;
	}
	else {
		sample = acting_probabilities(generator);
		if ((sample >= 0) && (sample <= 1/3)) {
			move_in_opposite_direction(&returnable_EA);
			//timer_speed = ;
		}
		else if ( (sample >= 1/3) && (sample <= 2/3) ) {
			stay_still(&returnable_EA);
			//timer_speed = ;
		}
		else {
			jump(&returnable_EA);
			//timer_speed = ;
		}
	}
	al_set_timer_speed(acting_timer, timer_speed);
}


