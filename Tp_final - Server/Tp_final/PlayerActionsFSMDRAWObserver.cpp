#include "PlayerActionsFSMDRAWObserver.h"


PlayerActionsFSMDRAWObserver::PlayerActionsFSMDRAWObserver(PlayerActionsFSM* fsm, CharacterActionsEventGenerator* ev_gen, Player* player)
{
	this->fsm = fsm;
	this->player = player;
	this->drawer = Userdata::drawer;
	this->ev_gen = ev_gen;
}


PlayerActionsFSMDRAWObserver::~PlayerActionsFSMDRAWObserver()
{
}

void PlayerActionsFSMDRAWObserver::update() {
	Direction dir = get_character_graph_direction(player->get_sense());

	if (fsm->obs_info.start_walking_graph) {
		
		MOVE_EventPackage* ev_pack = static_cast<MOVE_EventPackage*>(fsm->get_fsm_ev_pack());
		Direction dir = get_character_graph_direction(ev_pack->give_me_your_direction());
		drawer->startDraw(player_WALKING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_WALKING;
	}
	else if (fsm->obs_info.start_attacking_graph) {
		drawer->startDraw(player_ATTACKING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_ATTACKING;
	}
	else if (fsm->obs_info.start_falling_graph) {
		drawer->startDraw(player_FALLING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_FALLING;
	}

	else if (fsm->obs_info.start_jumping_graph) {
		drawer->startDraw(player_JUMPING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_JUMPING;
	}

	else if (fsm->obs_info.start_jumping_forward_graph) {
		drawer->startDraw(player_JUMPING_FOWARD, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_JUMPING_FOWARD;
	}

	else if (fsm->obs_info.dying_graph) {
		drawer->startDraw(player_DYING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_DYING;
	}

	else if (fsm->obs_info.reset_graph) {
		drawer->startDraw(player_IDLE, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_IDLE;
	}
	else if (fsm->obs_info.start_pushing_graph) {
		drawer->startDraw(player_PUSHING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_PUSHING;
	}
	else if (fsm->obs_questions.should_interrupt_movement) {
		fsm->obs_answers.should_interrupt_movement = drawer->secuenceOver(player->id);
	}
	else if (fsm->obs_questions.should_interrupt_attack) {
		fsm->obs_answers.should_interrupt_attack = drawer->secuenceOver(player->id);
	}
	else if (fsm->obs_info.interrupt_movement) {
		ev_gen->append_new_event(new FINISHED_MOVEMENT_EventPackage(), 0);
	}
	else if (fsm->obs_info.interrupt_attack) {
		ev_gen->append_new_event(new FINISHED_ATTACK_EventPackage(), 0);
	}
}


Direction PlayerActionsFSMDRAWObserver::get_character_graph_direction(Sense_type sense) {
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

Direction PlayerActionsFSMDRAWObserver::get_character_graph_direction(Direction_type direction) {
	Direction returnable = Direction::None;
	switch (direction) {
	case Direction_type::Left:
		returnable = Direction::Left;
		break;
	case Direction_type::Right:
		returnable = Direction::Right;
		break;
	default:
		returnable = Direction::None;
		break;
	}
	return returnable;
}

