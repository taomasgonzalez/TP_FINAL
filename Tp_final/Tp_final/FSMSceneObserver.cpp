#include "FSMSceneObserver.h"



FSMSceneObserver::FSMSceneObserver(FSM* fsm, Scene* scenario)
{
	this->fsm = fsm;
	this->scenario = scenario;
}


FSMSceneObserver::~FSMSceneObserver()
{
}

void FSMSceneObserver::update() {
	if (fsm->end_game) {
		scenario->finish_game();
	}
	if (fsm->start_game) {
		scenario->gameInit();
	}
	if (fsm->execute_action) {
		
	}
}