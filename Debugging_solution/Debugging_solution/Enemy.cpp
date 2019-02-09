#include "Enemy.h"


std::uniform_real_distribution<double> Enemy::acting_probabilities = std::uniform_real_distribution<double>(0.0, 1.0);
unsigned Enemy::seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine Enemy::generator = std::default_random_engine(seed);

Enemy::Enemy(unsigned  int id, Sense_type sense) : Character(id, sense)
{
	acting_timer = al_create_timer(1.0);
}


Enemy::~Enemy()
{
	al_destroy_timer(acting_timer);
}

/******************************************
**************is_enemy*********************
*******************************************
*is_enemy informs the user whether the object is an enemy or not.
*	INPUT:
*		1) void.
*	OUTPUT:
*		a boolean that is always true because this object is an Enemy.
*/
bool Enemy::is_enemy() {
	return true;
}

void Enemy::unfreeze()
{
}

void Enemy::be_hit()
{
}

/******************************************
**************get_acting_timer*********************
*******************************************
*get_acting_timer returns the timer by which the Enemy will act.
*	INPUT:
*		1) void.
*	OUTPUT:
*		the timer by which the Enemy will act.
*/
ALLEGRO_TIMER * Enemy::get_acting_timer() {
	return this->acting_timer;
}

/******************************************
**************move_in_same_direction*******
*******************************************
*move_in_same_direction modifies EA_info structure so that the Enemy will move in the direction it is facing
*when the Enemy Action is executed.
*	INPUT:
*		1)next_enemy_action : EA_info to be modified.
*	OUTPUT:
*		a boolean that is true if the movement can be performed.
*/
bool Enemy::move_in_same_direction(Action_info * next_enemy_action)
{
	if (next_enemy_action->valid = can_move_in_same_direction()) {
		EA_info_common_filling(next_enemy_action);
		next_enemy_action->action = Action_type::Move;
		if (my_sense == Sense_type::Left)
			next_enemy_action->final_pos_x = pos_x - 1;
		else if (my_sense == Sense_type::Right)
			next_enemy_action->final_pos_x = pos_x + 1;
	}
	return next_enemy_action->valid;
}
/******************************************
***********move_in_opposite_direction******
*******************************************
*move_in_opposite_direction modifies EA_info structure so that the Enemy will move in the opposite the direction it is facing
*when the Enemy Action is executed.
*	INPUT:
*		1)next_enemy_action : EA_info to be modified.
*	OUTPUT:
*		a boolean that is true if the movement can be performed.
*/
bool Enemy::move_in_opposite_direction(Action_info * next_enemy_action)
{
	if (next_enemy_action->valid = can_move_in_opposite_direction()) {
		EA_info_common_filling(next_enemy_action);
		next_enemy_action->action = Action_type::Move;
		if (this->my_sense == Sense_type::Left)
			next_enemy_action->final_pos_x = pos_x + 1;
		else if (this->my_sense == Sense_type::Right)
			next_enemy_action->final_pos_x = pos_x - 1;
	}
	return next_enemy_action->valid;
}
/******************************************
***********stay_still******
*******************************************
*stay_still modifies an EA_info structure so that the Enemy will stay in the same position
*when the Enemy Action is executed.
*	INPUT:
*		1) next_enemy_action : EA_info to be modified.
*	OUTPUT:
*		void.
*/
void Enemy::stay_still(Action_info * next_enemy_action)
{
	next_enemy_action->valid = true;
	EA_info_common_filling(next_enemy_action);
	next_enemy_action->action = Action_type::Move;
	next_enemy_action->final_pos_x = pos_x;
	next_enemy_action->final_pos_y = pos_y;
}
/******************************************
********************jump*******************
*******************************************
*jump modifies EA_info structure so that the Enemy willjump when the Enemy Action is executed.
*	INPUT:
*		1) next_enemy_action : EA_info to be modified.
*	OUTPUT:
*		a boolean that is true if the movement can be performed.
*/
bool Enemy::jump(Action_info * next_enemy_action) {
	if (next_enemy_action->valid = can_move_in_opposite_direction()) {
		EA_info_common_filling(next_enemy_action);
		next_enemy_action->action = Action_type::Move;
		next_enemy_action->final_pos_y = pos_y + 1;
	}
	return next_enemy_action->valid;
}

void Enemy::freeze()
{
}

/******************************************
***********EA_info_common_filling**********
*******************************************
*EA_info_common_filling modifies an EA_info structure with general information like the Enemy's id.
*	INPUT:
*		1) next_enemy_action : EA_info to be modified.
*	OUTPUT:
*		void.
*/
void Enemy::EA_info_common_filling(Action_info * next_enemy_action) {
	next_enemy_action->my_info_header = Action_info_id::ENEMY_ACTION;
	next_enemy_action->id = id;
	next_enemy_action->is_local = true;
}
/******************************************
***********can_move_in_opposite_direction**********
*******************************************
*can_move_in_opposite_direction indicates whether it is possible for the Enemy to move_in_opposite_direction given the map conditions. 
*	INPUT:
*		1) void.
*	OUTPUT:
*		a boolean that is true if the movement could be performed.
*/
bool Enemy::can_move_in_opposite_direction() {
	questions_4_observer.can_move_in_opposite_direction = true;
	notify_obs();
	questions_4_observer.can_move_in_opposite_direction = false;
	return answers_4_observable.can_move_in_opposite_direction;
}
/******************************************
***********can_move_in_same_direction**********
*******************************************
*can_move_in_same_direction indicates whether it is possible for the Enemy to can_move_in_same_direction given the map conditions.
*	INPUT:
*		1) void.
*	OUTPUT:
*		a boolean that is true if the movement could be performed.
*/
bool Enemy::can_move_in_same_direction() {
	questions_4_observer.can_move_in_same_direction = true;
	notify_obs();
	questions_4_observer.can_move_in_same_direction = false;
	return answers_4_observable.can_move_in_same_direction;
}
/******************************************
***********can_jump**********
*******************************************
*can_jump indicates whether it is possible for the Enemy to jump given the map conditions.
*	INPUT:
*		1) void.
*	OUTPUT:
*		a boolean that is true if the movement could be performed.
*/
bool Enemy::can_jump() {
	questions_4_observer.can_jump = true;
	notify_obs();
	questions_4_observer.can_jump = false;
	return answers_4_observable.can_jump;
}