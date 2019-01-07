#include "FSMSceneObserver.h"



FSMSceneObserver::FSMSceneObserver(Fsm* fsm, Scene* scenario)
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
}