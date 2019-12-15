#include "GraphicCharacterFSMRoutines.h"
#include "GraphicCharacterFSM.h"

void do_nothing(void* data) {

}
void disappear(void* data) {
	GraphicCharacterFSM* fsm = (GraphicCharacterFSM*)data;
	fsm->should_disappear = true;
	fsm->notify_obs();
	fsm->should_disappear = false;
}

void move(void* data) {
	GraphicCharacterFSM* fsm = (GraphicCharacterFSM*)data;
	fsm->should_move = true;
	fsm->notify_obs();
	fsm->should_move = false;
}

void die(void* data) {
	GraphicCharacterFSM* fsm = (GraphicCharacterFSM*)data;
	fsm->should_die = true;
	fsm->notify_obs();
	fsm->should_die = false;
}

void revive(void * data) {
	GraphicCharacterFSM* fsm = (GraphicCharacterFSM*)data;
	fsm->should_revive = true;
	fsm->notify_obs();
	fsm->should_revive = false;
}

