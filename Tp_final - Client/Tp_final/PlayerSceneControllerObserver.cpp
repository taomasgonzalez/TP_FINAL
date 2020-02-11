#include "PlayerSceneControllerObserver.h"



PlayerSceneControllerObserver::PlayerSceneControllerObserver(Scene* my_scenario, Character* character)
{
	this->scenario = my_scenario;
	this->character = character;
	this->fsm = static_cast<CharacterActionsFSM*>(character->ev_handler->get_fsm());
}


PlayerSceneControllerObserver::~PlayerSceneControllerObserver()
{
}

void PlayerSceneControllerObserver::update() {

		if (fsm->obs_info.keep_moving) {

		//The saved event loaded previously is finally put into the FSM by ScenarioEventsObserver
		scenario->load_saved_event_r();
		fsm->obs_info.next_move_pending = true;
		//ev_gen->append_new_event(new WALKED_EventPackage(scenario->assistant_queue->front().my_direction), 0);
		}
}
