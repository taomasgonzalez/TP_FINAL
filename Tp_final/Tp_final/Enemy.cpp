#include "Enemy.h"


std::uniform_real_distribution<double> Enemy::acting_probabilities = std::uniform_real_distribution<double>(0.0, 1.0);
unsigned Enemy::seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine Enemy::generator = std::default_random_engine(seed);

Enemy::Enemy(unsigned  int id) : Character(id)
{
	acting_timer = al_create_timer(1.0);
}


Enemy::~Enemy()
{
	al_destroy_timer(acting_timer);
}

bool Enemy::is_enemy() {
	return true;
}

ALLEGRO_TIMER * Enemy::get_acting_timer() {
	return this->acting_timer;
}

bool Enemy::move_in_same_direction(EA_info * next_enemy_action)
{
	if (next_enemy_action->valid = can_move_in_same_direction()) {
		EA_info_common_filling(next_enemy_action);
		next_enemy_action->action = Action_type::Move;
		if (this->my_sense == Sense_type::Left)
			next_enemy_action->final_pos_x = pos_x - 1;
		else if (this->get_sense == Sense_type::Right)
			next_enemy_action->final_pos_x = pos_x + 1;
	}
	return next_enemy_action->valid;
}

bool Enemy::move_in_opposite_direction(EA_info * next_enemy_action)
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

void Enemy::stay_still(EA_info * next_enemy_action)
{
	next_enemy_action->valid = true;
	EA_info_common_filling(next_enemy_action);
	next_enemy_action->action = Action_type::Move;
	next_enemy_action->final_pos_x = pos_x;
	next_enemy_action->final_pos_y = pos_y;
}

bool Enemy::jump(EA_info * next_enemy_action) {
	if (next_enemy_action->valid = can_move_in_opposite_direction()) {
		EA_info_common_filling(next_enemy_action);
		next_enemy_action->action = Action_type::Move;
		next_enemy_action->final_pos_y = pos_y + 1;
	}
	return next_enemy_action->valid;
}

void Enemy::EA_info_common_filling(EA_info * next_enemy_action) {
	next_enemy_action->id = id;
	next_enemy_action->is_local = true;
}

bool Enemy::can_move_in_opposite_direction() {
	questions_4_observer.can_move_in_opposite_direction = true;
	notify_obs();
	questions_4_observer.can_move_in_opposite_direction = false;
	return answers_4_observable.can_move_in_opposite_direction;
}
bool Enemy::can_move_in_same_direction() {
	questions_4_observer.can_move_in_same_direction = true;
	notify_obs();
	questions_4_observer.can_move_in_same_direction = false;
	return answers_4_observable.can_move_in_same_direction;
}

bool Enemy::can_jump() {
	questions_4_observer.can_jump = true;
	notify_obs();
	questions_4_observer.can_jump = false;
	return answers_4_observable.can_jump;
}