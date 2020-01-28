#include "PurpleGuy.h"

double PurpleGuy::moving_speed = 300;

PurpleGuy::PurpleGuy(unsigned int id, Sense_type sense) :Enemy(id, sense)
{
	printable = Item_type::PURPLE_GUY;
	staying_still_time = 0.3;
	staying_still_timer = al_create_timer(staying_still_time);
	al_register_event_source(enemy_timers, al_get_timer_event_source(staying_still_timer));
	al_set_timer_speed(staying_still_timer, staying_still_time);
}


PurpleGuy::~PurpleGuy()
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
Action_info PurpleGuy::act(){

	Action_info returnable_EA = Action_info();
	double sample = acting_probabilities(generator);
	returnable_EA.valid = true;
	move_in_opposite_direction(&returnable_EA);

	//while (!returnable_EA.valid){

	//	if ((sample >= 0) && (sample <= 0.6)) 			//0.6 probability
	//		stay_still(&returnable_EA);
	//	
	//	else if ((sample >= 0.6) && (sample <= 0.9)) {							//0.3 probability
	//		sample = acting_probabilities(generator); 

	//		while (!returnable_EA.valid) {
	//			if ((sample >= 0) && (sample <= 1.0 / 3.0)) { 						//1/3 probability
	//				if (!jump(&returnable_EA))			//en ningún caso debería ser posible no saltar
	//					sample = 0.5;
	//			}
	//			else if ((sample >= 1.0 / 3.0) && (sample <= 2.0 / 3.0)) {			//1/3 probability
	//				if (!move_in_opposite_direction(&returnable_EA))
	//					sample = 0.9;
	//			}
	//			else																//1/3 probability
	//				if(!move_in_same_direction(&returnable_EA))
	//					sample = 0.5; //moves in the other direction
	//		}
	//	}
	//	else if ((sample >= 0.9) && (sample <= 1.0)) 		//0.1 probability
	//		stay_still(&returnable_EA);
		
	//}

	return returnable_EA;
}

/******************************************
**************move_to_nearest_player*******
*******************************************
*move_to_nearest_player returns modifies an EA_info structure so that the Enemy Action will make the PurpleGuy move
*to the nearest player, taking the shortest route towards it.
*	INPUT:
*		1) next_enemy_action : EA_info to be modified.
*	OUTPUT:
*		void.
*/
void PurpleGuy::move_to_nearest_player(Action_info * next_enemy_action) { //NOTE:: Watch out that EA_info has ALL the fileds correctly loaded!!!!!
	EA_info_common_filling(next_enemy_action);
	//set_action_4_obs(*next_enemy_action);
	purple_questions_4_observer.calculate_shortest_distance = true;
	notify_obs();
	purple_questions_4_observer.calculate_shortest_distance = false;

	next_enemy_action->final_pos_x = next_movement_2_nearest_player.fil;
	next_enemy_action->final_pos_y = next_movement_2_nearest_player.col;
	next_enemy_action->action = Action_type::Move;
	next_enemy_action->valid = true;
}


/******************************************
**************set_next_movement_2_nearest_player*******
*******************************************
*set_next_movement_2_nearest_player sets the final position in which the PurpleGuy should move as a result of calling
*move_to_nearest_player method. This method is designed to be called by an Observer.
*	INPUT:
*		1) final_pos : position the PurpleGuy guy should move to after calling move_to_nearest_player();
*	OUTPUT:
*		void.
*/
void PurpleGuy::set_next_movement_2_nearest_player(Position final_pos) {
	this->next_movement_2_nearest_player = final_pos;
}

