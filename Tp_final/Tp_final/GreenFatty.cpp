#include "GreenFatty.h"

double GreenFatty::moving_speed = 200;

GreenFatty::GreenFatty(unsigned int id) : Enemy(id)
{
	printable = 'G';
}


GreenFatty::~GreenFatty()
{
}

void GreenFatty::act() {
	al_stop_timer(acting_timer);
	double sample = acting_probabilities(generator);
	double timer_speed;
	if ((sample >= 0) && (sample <= 0.3)) {			//0.3 probability
		//disparar fuego
		//timer_speed= 
	}
	else if ((sample >= 0.3) && (sample <= 0.9)) {		//0.6 probability
		//camina en el sentido que estaba mirando
		//timer_speed= 

	}
	else{												//0.1 probability
		sample = acting_probabilities(generator);
		if ((sample >= 0) && (sample <= 0.3)) {			//1/3 probability
			//saltar
			//timer_speed= 
		}
		else if ((sample >= 1 / 3) && (sample <= 2 / 3)) {//1/3 probability
			//moverse en direccion contraria
			//timer_speed= 
		}
		else {											//1/3 probability
			//quedarse quieto por 0.5 segundos
			//timer_speed = ;
		}
	}
	al_set_timer_speed(acting_timer, timer_speed);
}