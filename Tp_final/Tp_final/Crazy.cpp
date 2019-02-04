#include "Crazy.h"

double Crazy::moving_speed = 300;

Crazy::Crazy(unsigned int id): Enemy(id)
{
	printable = Item_type::CRAZY;
}


Crazy::~Crazy()
{
}

void Crazy::act() {
	double sample = acting_probabilities(generator);
	double timer_speed;

	if (sample <= 0.75) {
		//moverse en misma direccion
		//timer_speed = ;
	}
	else {
		sample = acting_probabilities(generator);
		if ((sample >= 0) && (sample <= 1/3)) {
			//moverse en direccion contraria
			//timer_speed = ;
		}
		else if ( (sample >= 1/3) && (sample <= 2/3) ) {
			//quedarse quieto.
			//timer_speed = ;
		}
		else {
			//saltar
			//timer_speed = ;
		}
	}
	//al_set_timer_speed(acting_timer);

}


