#include "GraphicAttackCharacterFSMRoutines.h"
#include "GraphicAttackCharacterFSM.h"


void attack(void* data) {
	GraphicAttackCharacterFSM* fsm = (GraphicAttackCharacterFSM*)data;
	fsm->should_attack = true;
	fsm->notify_obs();
	fsm->should_attack = false;
}

void finish_attack(void * data) {
	GraphicAttackCharacterFSM* fsm = (GraphicAttackCharacterFSM*)data;
	fsm->should_finish_attack = true;
	fsm->notify_obs();
	fsm->should_finish_attack = false;
}
