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
		bool should_be_hit = false;
		perform_character_movement(ev_pack->to_Action_info(), should_be_hit);
	}

	else if (scenario->load_action_on_char) {
		if (scenario->get_action_to_be_loaded_id() == character->id) 
			append_action_to_character(scenario->get_action_to_be_loaded());
	}
	
}

void CharacterSceneObserver::kill_character() {
	ev_gen->append_new_event(new DIED_EventPackage(), 0);

}

void CharacterSceneObserver::append_action_to_character(Action_info action) {
	EventPackage* ev_pack = NULL;
	if (action.action == Action_type::Attack)
		ev_pack = new ATTACK_EventPackage();
	
	else if (action.action == Action_type::Move) {
		switch (action.my_direction) {
			case Direction_type::Jump_Right:
			case Direction_type::Jump_Left:
				ev_pack = new JUMPED_FORWARD_EventPackage(action.my_direction);
				break;
			case Direction_type::Jump_Straight:
				ev_pack = new JUMPED_EventPackage();
				break;
			case Direction_type::Left:
			case Direction_type::Right:
				ev_pack = new WALKED_EventPackage(action.my_direction);
				break;
		}
	}
	ev_gen->append_new_event(ev_pack,0);
}
/*
void CharacterSceneObserver::perform_character_movement(Action_info* action, bool& should_die) {

	//fsm->obs_answers.can_perform_movement = scenario->execute_action(action->to_Action_info(), should_die, should_hit);
	if (should_die)
		kill_character();

}*/