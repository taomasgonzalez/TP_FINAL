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
		ATTACK_EventPackage* ev_pack = (ATTACK_EventPackage*)fsm->get_fsm_ev_pack();
		//fsm->obs_answers.can_attack = scene->check_attack(ev_pack->to_Action_info());
	}
	else if (fsm->obs_info.perform_logical_attack) {
		Direction_type attack_direction = fsm->get_current_action_direction();
		unsigned int current_character_id = fsm->get_character_id();
		//scene->execute_attack(ev_pack->to_Action_info())
	}
	else if (fsm->obs_questions.can_perform_movement) {
		MOVE_EventPackage* ev_pack =(MOVE_EventPackage*) fsm->get_fsm_ev_pack();
		//fsm->obs_answers.can_perform_movement = scenario->check_movement(ev_pack->to_Action_info());
	}
	else if (fsm->obs_info.perform_logical_movement) {
		Direction_type movement_direction = fsm->get_current_action_direction();
		unsigned int current_character_id = fsm->get_character_id();
		MOVE_EventPackage* ev_pack = (MOVE_EventPackage*)fsm->get_fsm_ev_pack();
		bool should_die = false;
		//fsm->obs_answers.can_perform_movement = scenario->execute_movement(ev_pack->to_Action_info(), &should_die);
		if (should_die) 
			kill_character();
	}
}

void CharacterSceneObserver::kill_character() {
	ev_gen->append_new_event(new DIED_EventPackage(), 0);
}

