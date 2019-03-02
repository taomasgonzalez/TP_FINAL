#include "SceneCharacterObserver.h"



SceneCharacterObserver::SceneCharacterObserver(Scene* scenario, Character* character)
{
	this->scenario = scenario;
	this->character = character;
	this->fsm = (CharacterActionsFSM*)character->get_my_fsm();
	this->ev_gen = (CharacterActionsEventGenerator*)character->get_my_ev_gen();
}


SceneCharacterObserver::~SceneCharacterObserver()
{
}

void SceneCharacterObserver::update() {

		if (scenario->load_action_on_char) {
		if (scenario->get_action_to_be_loaded_id() == character->id)
			append_action_to_character(scenario->get_action_to_be_loaded());
		}
}

void SceneCharacterObserver::append_action_to_character(Action_info action) {
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
	ev_gen->append_new_event(ev_pack, 0);
}
