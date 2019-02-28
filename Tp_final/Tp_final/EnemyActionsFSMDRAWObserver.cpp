#include "EnemyActionsFSMDRAWObserver.h"


EnemyActionsFSMDRAWObserver::EnemyActionsFSMDRAWObserver(EnemyActionsFSM* fsm, CharacterActionsEventGenerator* ev_gen, Enemy* enemy)
{
	this->fsm = fsm;
	this->drawer = Userdata::drawer;
	this->enemy = enemy;
	this->ev_gen = ev_gen;
}


EnemyActionsFSMDRAWObserver::~EnemyActionsFSMDRAWObserver()
{
}

void EnemyActionsFSMDRAWObserver::update() {
	Direction dir = get_character_graph_direction(enemy->get_sense());

	if (fsm->obs_info.start_walking_graph) {
		drawer->startDraw(enemy_WALKING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		check_if_finished_and_notify(enemy_WALKING);
	}

	else if (fsm->obs_info.start_attacking_graph) {
		drawer->startDraw(enemy_ATTACKING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		check_if_finished_and_notify(enemy_ATTACKING);
	}

	else if (fsm->obs_info.start_falling_graph) {
		drawer->startDraw(enemy_FALLING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		check_if_finished_and_notify(enemy_FALLING);
	}

	else if (fsm->obs_info.start_jumping_graph) {
		drawer->startDraw(enemy_JUMPING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		check_if_finished_and_notify(enemy_JUMPING);
	}

	else if (fsm->obs_info.start_jumping_forward_graph) {
		drawer->startDraw(enemy_JUMPING_FOWARD, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		check_if_finished_and_notify(enemy_JUMPING_FOWARD);
	}

	else if (fsm->obs_info.dying_graph) {
		drawer->startDraw(enemy_DYING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		check_if_finished_and_notify(enemy_DYING);
	}

	else if (fsm->obs_info.reset_graph) {
		drawer->startDraw(enemy_IDLE, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		check_if_finished_and_notify(enemy_IDLE);
	}
	else if (fsm->obs_info.interrupt_movement) {
		ev_gen->append_new_event(new FINISHED_MOVEMENT_EventPackage(), 0);
	}
	else if (fsm->obs_info.interrupt_attack) {
		ev_gen->append_new_event(new FINISHED_ATTACK_EventPackage(), 0);
	}

}
void EnemyActionsFSMDRAWObserver::check_if_finished_and_notify(ENEMY_STATE state) {
	if (drawer->secuenceOver(enemy->id)) {
		if (state == enemy_ATTACKING)
			ev_gen->append_new_event(new FINISHED_ATTACK_EventPackage, 0);
		else
			ev_gen->append_new_event(new FINISHED_MOVEMENT_EventPackage(), 0);
	}
}

Direction EnemyActionsFSMDRAWObserver::get_character_graph_direction(Sense_type sense) {
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

