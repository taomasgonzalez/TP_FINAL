#include "Enemy.h"
#include "EnemyActionsFSM.h"
#include "EnemyActionsFSMDRAWObserver.h"
#include "MapThingEventGenerator.h"

std::uniform_real_distribution<double> Enemy::acting_probabilities = std::uniform_real_distribution<double>(0.0, 1.0);
unsigned Enemy::seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine Enemy::generator = std::default_random_engine(seed);

Enemy::Enemy(unsigned  int id, Sense_type sense) : Character(id, sense)
{

	EnemyActionsFSM* fsm = new EnemyActionsFSM(this);
	//en el momento en que necesite mas timers para EnemyActionsFSM, tendre que overridiear la funcion get_all_my_timers!
	MapThingEventGenerator* ev_gen = new MapThingEventGenerator();
	fsm->add_observer(new EnemyActionsFSMDRAWObserver(fsm, ev_gen, this));
	ev_handler = new EventHandler(fsm, ev_gen);
	enemy_timers = al_create_event_queue();
	
}


Enemy::~Enemy()
{
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
	EA_info_common_filling(next_enemy_action);

	next_enemy_action->action = Action_type::Move;

	if (my_sense == Sense_type::Left){
		next_enemy_action->final_pos_y = pos_y;
		next_enemy_action->final_pos_x = pos_x - 1;
		next_enemy_action->my_direction = Direction_type::Left;
	}
	else if (my_sense == Sense_type::Right){
		next_enemy_action->final_pos_y = pos_y;
		next_enemy_action->final_pos_x = pos_x + 1;
		next_enemy_action->my_direction = Direction_type::Right;
	}
	set_action_4_obs(*next_enemy_action);

	return (next_enemy_action->valid = can_make_movement());
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
	EA_info_common_filling(next_enemy_action);
	next_enemy_action->action = Action_type::Move;

	if (my_sense == Sense_type::Left) {
		next_enemy_action->final_pos_y = pos_y;
		next_enemy_action->final_pos_x = pos_x + 1;
		next_enemy_action->my_direction = Direction_type::Right;
		this->my_sense = Sense_type::Right;

	}
	else if (my_sense == Sense_type::Right) {
		next_enemy_action->final_pos_y = pos_y;
		next_enemy_action->final_pos_x = pos_x - 1;
		next_enemy_action->my_direction = Direction_type::Left;
		this->my_sense = Sense_type::Left;

	}

	return (next_enemy_action->valid = can_make_movement());

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
	EA_info_common_filling(next_enemy_action);
	next_enemy_action->action = Action_type::Move;
	next_enemy_action->final_pos_x = pos_x;
	next_enemy_action->final_pos_y = pos_y;
	next_enemy_action->valid = true;

}
bool Enemy::can_make_movement()
{
	enemy_questions_4_observer.can_make_movement = true;
	notify_obs();
	enemy_questions_4_observer.can_make_movement = false;

	return enemy_answers_4_observable.can_make_movement;
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

	EA_info_common_filling(next_enemy_action);

	next_enemy_action->action = Action_type::Move;
	next_enemy_action->final_pos_x = pos_x - 1;
	next_enemy_action->final_pos_y = pos_y;
	next_enemy_action->my_direction = Direction_type::Jump_Straight;
	al_start_timer(staying_still_timer);
	is_staying_still = true;
	return (next_enemy_action->valid = can_make_movement());
}

Action_info Enemy::get_action_4_obs()
{
	return action_4_obs;
}

void Enemy::set_action_4_obs(Action_info action) {

	this->action_4_obs= action;

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


bool Enemy::is_iddle() {
	bool returnable = true;
	ALLEGRO_EVENT al_event;

	if (!is_staying_still)
		returnable = Character::is_iddle();
	else {
		if (al_get_next_event(enemy_timers, &al_event))
			if (al_event.type == ALLEGRO_EVENT_TIMER)
				if (al_event.timer.source == staying_still_timer) {
					al_stop_timer(staying_still_timer);
					is_staying_still = false;
				}
		returnable = is_staying_still;
	}

	return returnable;
}


