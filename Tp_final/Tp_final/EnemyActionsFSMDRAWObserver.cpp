#include "EnemyActionsFSMDRAWObserver.h"

Direction get_character_graph_direction(Sense_type sense);

EnemyActionsFSMDRAWObserver::EnemyActionsFSMDRAWObserver(EnemyActionsFSM* fsm, Enemy* enemy)
{
	this->fsm = fsm;
	this->drawer = Userdata::drawer;
	this->enemy = enemy;
}


EnemyActionsFSMDRAWObserver::~EnemyActionsFSMDRAWObserver()
{
}

void EnemyActionsFSMDRAWObserver::update() {
	Direction dir = get_character_graph_direction(enemy->get_sense());

	if (fsm->obs_info.start_walking_graph) {
		drawer->startDraw(enemy_WALKING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}

	else if (fsm->obs_info.start_attacking_graph) {
		drawer->startDraw(enemy_ATTACKING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}

	else if (fsm->obs_info.start_falling_graph) {
		drawer->startDraw(enemy_FALLING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}

	else if (fsm->obs_info.start_jumping_graph) {
		drawer->startDraw(enemy_JUMPING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}

	else if (fsm->obs_info.start_jumping_forward_graph) {
		drawer->startDraw(enemy_JUMPING_FOWARD, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}

	else if (fsm->obs_info.dying_graph) {
		drawer->startDraw(enemy_DYING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}

	else if (fsm->obs_info.reset_graph) {
		drawer->startDraw(enemy_IDLE, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}

}
Direction get_character_graph_direction(Sense_type sense) {
	Direction returnable = Direction::None;
	switch (sense) {
	case Sense_type::Left:
		returnable = Direction::Left;
		break;
	case Sense_type::Right:
		returnable = Direction::Right;
		break;
	default:
		returnable = Direction::None;
		break;
	}
	return returnable;
}