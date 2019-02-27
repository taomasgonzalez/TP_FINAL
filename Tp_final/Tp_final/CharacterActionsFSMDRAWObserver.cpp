#include "CharacterActionsFSMDRAWObserver.h"

CharacterActionsFSMDRAWObserver::CharacterActionsFSMDRAWObserver(CharacterActionsFSM * fsm)
{
	this->fsm = fsm;
	this->drawer = Userdata::drawer;
}

CharacterActionsFSMDRAWObserver::~CharacterActionsFSMDRAWObserver()
{

}


void CharacterActionsFSMDRAWObserver::update() {

}

