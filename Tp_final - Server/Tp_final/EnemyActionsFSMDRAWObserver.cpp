#include "EnemyActionsFSMDRAWObserver.h"


EnemyActionsFSMDRAWObserver::EnemyActionsFSMDRAWObserver(EnemyActionsFSM* fsm, EventGenerator* ev_gen, Enemy* enemy)
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
	Direction dir;

	if (first_update) {
		drawer->add_observer(enemy->id, this);
		first_update = false;
	}
	if (fsm->obs_info.start_walking_graph) {
		dir = get_character_graph_direction(fsm->get_current_action_direction());
		enemy->set_sense(dir_to_sense(fsm->get_current_action_direction()));
		drawer->startDraw(enemy_WALKING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_WALKING;
	}

	else if (fsm->obs_info.start_attacking_graph) {
		dir = get_character_graph_direction(fsm->get_current_action_direction());
		drawer->startDraw(enemy_ATTACKING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_ATTACKING;
	}

	else if (fsm->obs_info.start_falling_graph) {
		dir = get_character_graph_direction(fsm->get_current_action_direction());
		drawer->startDraw(enemy_FALLING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_FALLING;
	}

	else if (fsm->obs_info.start_jumping_graph) {
		dir = get_character_graph_direction(fsm->get_current_action_direction());
		drawer->startDraw(enemy_JUMPING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_JUMPING;
	}

	else if (fsm->obs_info.start_jumping_forward_graph) {
		//dir = get_character_graph_direction(fsm->get_current_action_direction());
		JUMPED_FORWARD_EventPackage* ev_pack = static_cast<JUMPED_FORWARD_EventPackage*>(fsm->get_fsm_ev_pack());
		dir = get_character_graph_direction(ev_pack->jumping_direction);
		drawer->startDraw(player_JUMPING_FOWARD, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_JUMPING_FOWARD;
	}

	else if (fsm->obs_info.dying_graph) {
		dir = get_character_graph_direction(enemy->get_sense());
		drawer->startDraw(enemy_DYING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		curr_state = enemy_DYING;
	}

	else if (fsm->obs_info.reset_graph) {
		dir = get_character_graph_direction(enemy->get_sense());
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
	else if (drawer->finished_drawing_step(enemy->id)) {
		ev_gen->append_new_event(new FINISHED_GRAPH_STEP_EventPackage(), 0);
	}
	else if (fsm->obs_info.disappear_graph) {
		drawer->disactiveObj(enemy->id);
	}

	//enemy_got_hit related
	/*
	else if (fsm->enemyObs_answers.should_unfreeze) {
		enemy->amount_of_hits_taken--;
		if (enemy->amount_of_hits_taken == 0) {
			dir = get_character_graph_direction(enemy->get_sense());
			drawer->startDraw(enemy_IDLE, enemy->id, dir, enemy->pos_x, enemy->pos_y);
			ev_gen->append_new_event(new UNFREEZE_EventPackage(), 0);
		}
	}
	else if (fsm->enemyObs_answers.should_start_defrost) {
		fsm->enemyObs_answers.should_start_defrost = false;
		enemy->amount_of_hits_taken = 3;
		dir = get_character_graph_direction(enemy->get_sense());
		drawer->startDraw(enemy_TRAPPED_2, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		ev_gen->append_new_event(new UNFROZE_EventPackage(), 0);
	}*/
	else if (fsm->enemyObs_info.start_freezing_state1_graph){
		dir = get_character_graph_direction(enemy->get_sense());
		drawer->startDraw(enemy_TRAPPED_1, enemy->id, dir, enemy->pos_x, enemy->pos_y);
		}
	else if (fsm->enemyObs_info.start_freezing_state2_graph) {
		dir = get_character_graph_direction(enemy->get_sense());
		drawer->startDraw(enemy_TRAPPED_2, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}
	else if (fsm->enemyObs_info.start_freezing_state3_graph) {
		dir = get_character_graph_direction(enemy->get_sense());
		drawer->startDraw(enemy_TRAPPED_3, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}
	else if (fsm->enemyObs_info.start_fozen_graph) {
		dir = get_character_graph_direction(enemy->get_sense());
		drawer->startDraw(enemy_INBALL_IDLE, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}
	else if (fsm->enemyObs_info.start_ballCharging_graph) {
		dir = get_character_graph_direction(enemy->get_sense());
		drawer->startDraw(enemy_INBALL_MOVING, enemy->id, dir, enemy->pos_x, enemy->pos_y);
	}


}

Direction EnemyActionsFSMDRAWObserver::get_character_graph_direction(Direction_type direction) {
	Direction returnable = Direction::None;
	switch (direction) {
	case Direction_type::Left:
	case Direction_type::Jump_Left:
		returnable = Direction::Left;
		break;
	case Direction_type::Right:
	case Direction_type::Jump_Right:
		returnable = Direction::Right;
		break;
	default:
		returnable = Direction::None;
		break;
	}
	return returnable;
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
Sense_type EnemyActionsFSMDRAWObserver::dir_to_sense(Direction_type sense) {
	Sense_type returnable = Sense_type::None;
	switch (sense) {
	case Direction_type::Left:
		returnable = Sense_type::Left;
		break;
	case Direction_type::Right:
		returnable = Sense_type::Right;
		break;
	default:
		returnable = Sense_type::None;
		break;
	}
	return returnable;
}

