#include "CharacterSceneObserver.h"



CharacterSceneObserver::CharacterSceneObserver(Scene* scenario, Character* character)
{
	this->scenario = scenario;
	this->character = character;
	this->fsm = (CharacterActionsFSM*)character->get_my_fsm();
	this->ev_gen = (CharacterActionsEventGenerator*)character->get_my_ev_gen();
}


CharacterSceneObserver::~CharacterSceneObserver()
{
}


void CharacterSceneObserver::update() {
	if (fsm->obs_questions.can_attack) {
		//fsm->obs_answers.can_attack = scene->check_attack();
	}
	else if (fsm->obs_questions.can_perform_movement) {
		//fsm->obs_answers.can_perform_movement = scene->check_movement();
	}
	else if (fsm->obs_info.perform_logical_attack) {
		Direction_type attack_direction = fsm->get_current_action_direction();
		unsigned int current_character_id = fsm->get_character_id();
		//perform attack.
	}
	else if (fsm->obs_info.perform_logical_movement) {
		Direction_type movement_direction = fsm->get_current_action_direction();
		unsigned int current_character_id = fsm->get_character_id();
		//perform movement.
	}
}