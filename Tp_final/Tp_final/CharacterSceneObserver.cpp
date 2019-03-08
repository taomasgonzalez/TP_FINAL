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
	if (fsm->obs_info.perform_logical_attack) {
		Sense_type sense = character->get_sense();
		//Direction_type dir = (sense == Sense_type::Right) ? Direction_type::Right : Direction_type::Left;
		unsigned int current_character_id = fsm->get_id();
		//scene->execute_attack(ev_pack->to_Action_info());
		ev_gen->append_new_event(new FINISHED_ATTACK_EventPackage(), 0);
	}
	if (fsm->obs_questions.can_perform_movement) {
		MOVE_EventPackage* ev_pack = static_cast<MOVE_EventPackage*>(fsm->get_fsm_ev_pack());
		//fsm->obs_answers.can_perform_movement = scenario->check_movement(ev_pack->to_Action_info());
	}
	if (fsm->obs_info.perform_logical_movement) {
		Direction_type movement_direction = fsm->get_current_action_direction();
		unsigned int current_character_id = fsm->get_id();
		MOVE_EventPackage* ev_pack = static_cast<MOVE_EventPackage*>(fsm->get_fsm_ev_pack());
		perform_movement(ev_pack->to_Action_info());
	}

}

void CharacterSceneObserver::kill_character() {
	ev_gen->append_new_event(new DIED_EventPackage(), 0);

}



