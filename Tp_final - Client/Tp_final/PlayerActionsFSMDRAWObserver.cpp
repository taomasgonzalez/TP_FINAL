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
	Direction dir;

	if (first_update) {
		drawer->add_observer(player->id, this);
		first_update = false;
	}

	if (fsm->obs_info.start_walking_graph) {
		dir = get_character_graph_direction(fsm->get_current_action_direction());
		player->set_sense(dir_to_sense(fsm->get_current_action_direction()));
		drawer->startDraw(player_WALKING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_WALKING;
	}
	else if (fsm->obs_info.start_attacking_graph) {
		dir = get_character_graph_direction(fsm->get_current_action_direction());
		drawer->startDraw(player_ATTACKING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_ATTACKING;
	}
	else if (fsm->obs_info.start_falling_graph) {
		dir = get_character_graph_direction(fsm->get_current_action_direction());
		drawer->startDraw(player_FALLING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_FALLING;
	}

	else if (fsm->obs_info.start_jumping_graph) {
		dir = get_character_graph_direction(fsm->get_current_action_direction());
		drawer->startDraw(player_JUMPING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_JUMPING;
	}

	else if (fsm->obs_info.start_jumping_forward_graph) {
		//dir = get_character_graph_direction(fsm->get_current_action_direction());
		JUMPED_FORWARD_EventPackage* ev_pack = static_cast<JUMPED_FORWARD_EventPackage*>(fsm->get_fsm_ev_pack());
		dir = get_character_graph_direction(ev_pack->jumping_direction);
		drawer->startDraw(player_JUMPING_FOWARD, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_JUMPING_FOWARD;
	}

	else if (fsm->obs_info.dying_graph) {
		dir = get_character_graph_direction(player->get_sense());
		drawer->startDraw(player_DYING, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_DYING;
	}

	else if (fsm->obs_info.reset_graph) {
		dir = get_character_graph_direction(player->get_sense());
		drawer->startDraw(player_IDLE, player->id, dir, player->pos_x, player->pos_y);
		curr_state = player_IDLE;
	}
	else if (fsm->obs_info.start_pushing_graph) {
		dir = get_character_graph_direction(fsm->get_current_action_direction());
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
	else if (drawer->finished_drawing_step(player->id)) {
		ev_gen->append_new_event(new FINISHED_GRAPH_STEP_EventPackage(), 0);
	}
	else if (fsm->obs_info.disappear_graph) {
		drawer->disactiveObj(player->id);
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

Sense_type PlayerActionsFSMDRAWObserver::dir_to_sense(Direction_type sense) {
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
