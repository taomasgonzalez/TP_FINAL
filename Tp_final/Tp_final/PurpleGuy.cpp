#include "PurpleGuy.h"

double PurpleGuy::moving_speed = 300;

PurpleGuy::PurpleGuy(unsigned int id) :Enemy(id)
{
	printable = Item_type::PURPLE_GUY;
}


PurpleGuy::~PurpleGuy()
{
}

EA_info PurpleGuy::act()
{
	EA_info returnable_EA;
	returnable_EA.is_local = true;
	al_stop_timer(acting_timer);
	double sample = acting_probabilities(generator);
	double timer_speed;
	if ((sample >= 0) && (sample <= 0.6)) {			//0.6 probability
		//moverse al jugador mas cercano
		//timer_speed= 
	}
	else if ((sample >= 0.6) && (sample <= 0.9)) {		//0.3 probability
		//moverse hacia direccion aleatoria
		sample = acting_probabilities(generator);
		if ((sample >= 0) && (sample <= 1.0/3.0)) {			//1/3 probability
			jump(&returnable_EA);
			//timer_speed= 
		}
		else if ((sample >= 1.0 / 3.0) && (sample <= 2.0 / 3.0)) {//1/3 probability
			move_in_opposite_direction(&returnable_EA);
			//timer_speed= 
		}
		else {
			move_in_same_direction(&returnable_EA);
			//timer_speed= 
		}
	}
	else if((sample >= 0.9) && (sample <= 1.0)){		//0.1 probability
		stay_still(&returnable_EA);
		//timer_speed= 
	}
	al_set_timer_speed(acting_timer, timer_speed);
	al_start_timer(acting_timer);
}
