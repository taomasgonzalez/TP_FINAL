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
	if (fsm->start_game) { //ver que onda en el caso de play again
		//scenario->gameInit();// ya se hace desde main
	}
	if (fsm->execute_action) { //puede ser un move, attack(ambos internos,de allegro, o externos, de networking) o un action request(networking)
		//a esta altura ya estan chequeados los movimientos, ya entran a la FSM chequeados
	}
}