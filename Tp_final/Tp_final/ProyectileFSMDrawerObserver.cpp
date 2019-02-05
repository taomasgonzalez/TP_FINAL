#include "ProyectileFSMDrawerObserver.h"



ProyectileFSMDrawerObserver::ProyectileFSMDrawerObserver(GraphicProyectileFSM* fsm, Drawer* drawer)
{
	this->fsm = fsm;
	this->drawer = drawer;
}


ProyectileFSMDrawerObserver::~ProyectileFSMDrawerObserver()
{
}

void ProyectileFSMDrawerObserver::update() {
	if (fsm->should_move) {

	}
	else if (fsm->should_impact) {

	}
	else if (fsm->should_disappear) {

	}
}
