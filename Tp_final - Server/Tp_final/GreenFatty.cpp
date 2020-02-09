#include "GreenFatty.h"

double GreenFatty::moving_speed = 200;

GreenFatty::GreenFatty(unsigned int id, Sense_type sense) : Enemy(id, sense)
{
	printable = Item_type::GREEN_FATTIE;

}


GreenFatty::~GreenFatty()
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
Action_info GreenFatty::act() {


	Action_info returnable_EA = Action_info();
	returnable_EA.valid = false;

	double sample = acting_probabilities(generator);

	if ((sample >= 0) && (sample <= 0.3)) 		//0.3 probability
		shoot_fireball(&returnable_EA);
	else if ((sample >= 0.3) && (sample <= 0.9)) {		//0.6 probability
		if (!move_in_same_direction(&returnable_EA))
			sample = 0.95;
	}
	else {												//0.1 probability
		sample = acting_probabilities(generator);

		if ((sample >= 0) && (sample <= 1.0 / 3.0)) {	//1/3 probability		
			if (!jump(&returnable_EA))
				sample = 0.5;
		}
		else if ((sample >= 1.0 / 3.0) && (sample <= 2.0 / 3.0)) {	//1/3 probability
			if (!move_in_opposite_direction(&returnable_EA))
				sample = 0.9;
		}
		else 										//1/3 probability
			stay_still(&returnable_EA);

	}
	if (!returnable_EA.valid)
		stay_still(&returnable_EA);

	if (EA_package_ID == FINISH_POINT_PACKAGE_ID_FOR_EA)
		EA_package_ID = START_POINT_PACKAGE_ID_FOR_EA;

	returnable_EA.ID = EA_package_ID++;
	//std::swap(returnable_EA.final_pos_x, returnable_EA.final_pos_y);


	return returnable_EA;
}


void GreenFatty::shoot_fireball(Action_info * next_enemy_action) {
	EA_info_common_filling(next_enemy_action);
	next_enemy_action->action = Action_type::Attack;
	next_enemy_action->final_pos_x = pos_x;
	next_enemy_action->final_pos_y = pos_y;
	next_enemy_action->valid = true;			//creating a fireball in the same place as the enemy should always be a valid action.
}

