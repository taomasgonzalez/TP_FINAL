#include "GreenFatty.h"

double GreenFatty::moving_speed = 200;

GreenFatty::GreenFatty(unsigned int id) : Enemy(id)
{
	printable = Item_type::GREEN_FATTIE;
}


GreenFatty::~GreenFatty()
{
}

EA_info GreenFatty::act() {

	EA_info returnable_EA;
	al_stop_timer(acting_timer);
	double sample = acting_probabilities(generator);
	double timer_speed;
	while (! returnable_EA.valid) {
		if ((sample >= 0) && (sample <= 0.3)) {			//0.3 probability
			shoot_fireball();
			//timer_speed= 
		}
		else if ((sample >= 0.3) && (sample <= 0.9)) {		//0.6 probability
			move_in_same_direction(&returnable_EA);
			//timer_speed = 
		}
		else {												//0.1 probability
			sample = acting_probabilities(generator);
			if ((sample >= 0) && (sample <= 1.0 / 3.0) && can_jump()) {			//1/3 probability
				jump(&returnable_EA);
				//timer_speed= 
			}
			else if ((sample >= 1.0 / 3.0) && (sample <= 2.0 / 3.0) ) { //1/3 probability
				move_in_opposite_direction(&returnable_EA);
				//timer_speed= 
			}
			else {							//1/3 probability
				stay_still(&returnable_EA);
				timer_speed = 1.0 / 2;
			}
		}
	}

	al_set_timer_speed(acting_timer, timer_speed);
}


void GreenFatty::shoot_fireball() {

}