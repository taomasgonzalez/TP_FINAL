#include "Crazy.h"

double Crazy::moving_speed = 300;

Crazy::Crazy(unsigned int id, Sense_type sense): Enemy(id, sense)
{
	printable = Item_type::CRAZY;
	staying_still_time = 0.3;
	staying_still_timer = al_create_timer(staying_still_time);
	al_register_event_source(enemy_timers, al_get_timer_event_source(staying_still_timer));
	al_set_timer_speed(staying_still_timer, staying_still_time);
}


Crazy::~Crazy()
{
}

/******************************************
**************act**************************
*******************************************
*act returns the Enemy Action information of the enemies next action. This method doesn't 
*execute the action, it just gives the information of the Enemy's next action so that it will be executed by correct Class (Scene).
*Only valid actions will be returned.
*	INPUT:
*		1) void.
*	OUTPUT:
*		EA_info containing all the information of the Enemy's next action. This action will always be local as the 
*		information is generated locally.
*/
Action_info Crazy::act() {

	Action_info returnable_EA;
	returnable_EA.valid = false;

	double sample = acting_probabilities(generator);

	if (sample <= 0.75) {
		if (!move_in_same_direction(&returnable_EA))
			sample = 0.8;
	}	
	else {
		sample = acting_probabilities(generator);

		if ((sample >= 0.0) && (sample <= 1.0 / 3.0)) {
			if (!move_in_opposite_direction(&returnable_EA)) 
				sample = 0.5;
		}
		else if ((sample >= 1.0 / 3.0) && (sample <= 2.0 / 3.0)) 
			stay_still(&returnable_EA);
		else 
			if(!jump(&returnable_EA))
				sample = 0.1;
	}

	if (EA_package_ID == FINISH_POINT_PACKAGE_ID_FOR_EA)
		EA_package_ID = START_POINT_PACKAGE_ID_FOR_EA;

	returnable_EA.ID = EA_package_ID++;

	//al_set_timer_speed(acting_timer, timer_speed);
	//al_start_timer(acting_timer);
	if(!returnable_EA.valid)
		stay_still(&returnable_EA);

	return returnable_EA;
}


