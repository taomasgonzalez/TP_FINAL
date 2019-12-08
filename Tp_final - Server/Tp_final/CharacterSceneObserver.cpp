#include "CharacterSceneObserver.h"


CharacterSceneObserver::CharacterSceneObserver(Scene* scenario, Character* character)
{
	this->scenario = scenario;
	this->character = character;
	this->fsm = static_cast<CharacterActionsFSM*>(character->ev_handler->get_fsm());
	this->ev_gen = static_cast<CharacterActionsEventGenerator*>(character->ev_handler->get_ev_gen());
}


CharacterSceneObserver::~CharacterSceneObserver()
{
}


void CharacterSceneObserver::update() {
	if (fsm->obs_info.perform_logical_attack) {
		Sense_type sense = character->get_sense();
		//Direction_type dir = (sense == Sense_type::Right) ? Direction_type::Right : Direction_type::Left;
		unsigned int current_character_id = fsm->get_id();
		//scene->execute_attack(ev_pack->to_Action_info());
		ev_gen->append_new_event(new FINISHED_ATTACK_EventPackage(), 0);
	}
	if (fsm->obs_questions.can_perform_movement) {
		MOVE_EventPackage ev_pack;
		Action_info info = ev_pack.to_Action_info();
		info.my_direction = fsm->get_current_action_direction();
		info.id = character->id;
		direction_to_deltas(&info);
		fsm->obs_answers.can_perform_movement = scenario->is_the_action_possible(&info);
	}
	if (fsm->obs_info.perform_logical_movement) {
		
		MOVE_EventPackage ev_pack;
		Action_info info = ev_pack.to_Action_info();
		info.my_direction = fsm->get_current_action_direction();
		info.id = character->id;
		direction_to_deltas(&info);
		perform_movement(info);
	}

}

void CharacterSceneObserver::kill_character() {
	ev_gen->append_new_event(new DIED_EventPackage(), 0);
}

void CharacterSceneObserver::direction_to_deltas(Action_info* action) {
	action->final_pos_x = character->pos_x;
	action->final_pos_y = character->pos_y;

	if (action->my_direction == Direction_type::Right)
		action->final_pos_x += 1;
	else if (action->my_direction == Direction_type::Jump_Straight)
		action->final_pos_y = character->pos_y + 1;
	else if (action->my_direction == Direction_type::Left)
		action->final_pos_y = character->pos_x - 1;
	else if (action->my_direction == Direction_type::Down)
		action->final_pos_y = character->pos_y - 1;
	else if (action->my_direction == Direction_type::Jump_Right) {
		action->final_pos_x = character->pos_x + 1;
		action->final_pos_y = character->pos_y + 1;
	}
	else if (action->my_direction == Direction_type::Jump_Left) {
		action->final_pos_x = character->pos_x - 1;
		action->final_pos_y = character->pos_y + 1;
	}
}


