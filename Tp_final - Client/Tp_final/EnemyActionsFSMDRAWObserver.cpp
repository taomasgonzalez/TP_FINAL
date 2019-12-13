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

	if (first_update) {
		drawer->add_observer(enemy->id, this);
		first_update = false;
	}
	if (fsm->obs_info.start_walking_graph) {
		drawer->startDraw(enemy_WALKING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_WALKING;
	}

	else if (fsm->obs_info.start_attacking_graph) {
		drawer->startDraw(enemy_ATTACKING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_ATTACKING;
	}

	else if (fsm->obs_info.start_falling_graph) {
		drawer->startDraw(enemy_FALLING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_FALLING;
	}

	else if (fsm->obs_info.start_jumping_graph) {
		drawer->startDraw(enemy_JUMPING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_JUMPING;
	}

	else if (fsm->obs_info.start_jumping_forward_graph) {
		drawer->startDraw(enemy_JUMPING_FOWARD, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_JUMPING_FOWARD;
	}

	else if (fsm->obs_info.dying_graph) {
		drawer->startDraw(enemy_DYING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_DYING;
	}

	else if (fsm->obs_info.reset_graph) {
		drawer->startDraw(enemy_IDLE, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_IDLE;
	}

	//fijarse de cambiar esto de manera tal que cuando se ejecute un draw se ponga en la cola de eventos un finished
	else if (fsm->obs_questions.should_interrupt_movement) {
		fsm->obs_answers.should_interrupt_movement = drawer->secuenceOver(enemy->id);
	}
	else if (fsm->obs_questions.should_interrupt_attack) {
		fsm->obs_answers.should_interrupt_attack = drawer->secuenceOver(enemy->id);
	}
	else if (fsm->obs_info.interrupt_movement) {
		ev_gen->append_new_event(new FINISHED_MOVEMENT_EventPackage(), 0);
	}
	else if (fsm->obs_info.interrupt_attack) {
		ev_gen->append_new_event(new FINISHED_ATTACK_EventPackage(), 0);
	}
	else if (fsm->obs_info.disappear_graph) {
		drawer->disactiveObj(enemy->id);
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

