#include "Crazy.h"

double Crazy::moving_speed = 300;

Crazy::Crazy(unsigned int id): Enemy(id)
{
	printable = Item_type::CRAZY;
}


Crazy::~Crazy()
{
}

EA_info* Crazy::act() {

	EA_info* returnable_EA = new EA_info();
	al_stop_timer(acting_timer);
	double sample = acting_probabilities(generator);
	double timer_speed;

	while (!returnable_EA->valid) 
		if (sample <= 0.75) 
			move_in_same_direction(returnable_EA) ? timer_speed = 0 : sample = 0.8;

		else {
			sample = acting_probabilities(generator);

			while (!returnable_EA->valid) {
				if ((sample >= 0.0) && (sample <= 1.0 / 3.0)) 
					move_in_opposite_direction(returnable_EA) ? timer_speed = 0 : sample = 0.5;

				else if ((sample >= 1.0 / 3.0) && (sample <= 2.0 / 3.0)) {
					stay_still(returnable_EA);
					timer_speed = 0;
				}
				else 
					jump(returnable_EA) ? timer_speed = 0 : sample = 0.1;

			}
		}

	al_set_timer_speed(acting_timer, timer_speed);
	al_start_timer(acting_timer);


	return returnable_EA;
}


