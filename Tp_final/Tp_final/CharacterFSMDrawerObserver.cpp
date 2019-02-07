#include "CharacterFSMDrawerObserver.h"



CharacterFSMDrawerObserver::CharacterFSMDrawerObserver(GraphicCharacterFSM* fsm, Drawer* drawer)
{
	this->fsm = fsm;
	this->drawer = drawer;
}


CharacterFSMDrawerObserver::~CharacterFSMDrawerObserver()
{
}

void CharacterFSMDrawerObserver::update() {
	if (fsm->should_move) {

	}
	else if (fsm->should_attack) {

	}
	else if (fsm->should_disappear) {

	}
}

