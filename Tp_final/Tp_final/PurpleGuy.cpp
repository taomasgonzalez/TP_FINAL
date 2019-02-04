#include "PurpleGuy.h"

double PurpleGuy::moving_speed = 300;

PurpleGuy::PurpleGuy(unsigned int id) :Enemy(id)
{
	printable = 'P';
}


PurpleGuy::~PurpleGuy()
{
}

void PurpleGuy::act()
{
	al_stop_timer(acting_timer);
	double sample = acting_probabilities(generator);
	double timer_speed;
	if ((sample >= 0) && (sample <= 0.6)) {			//0.6 probability
		//moverse al jugador mas cercano
		//timer_speed= 
	}
	else if ((sample >= 0.6) && (sample <= 0.9)) {		//0.3 probability
		//moverse hacia direccion aleatoria
		//timer_speed= 
	}
	else if((sample >= 0.9) && (sample <= 1.0)){		//0.1 probability
		//quedarse quieto.
		//timer_speed= 
	}
	al_set_timer_speed(acting_timer, timer_speed);
	al_start_timer(acting_timer);
}
