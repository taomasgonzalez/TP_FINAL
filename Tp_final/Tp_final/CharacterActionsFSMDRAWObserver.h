#pragma once
#include "DRAW.h"
#include "CharacterActionsFSM.h"
#include "Observer.h"

class CharacterActionsFSMDRAWObserver:public Observer
{
public:
	CharacterActionsFSMDRAWObserver(CharacterActionsFSM* fsm);

	~CharacterActionsFSMDRAWObserver();

	void update();

private:
	CharacterActionsFSM * fsm = NULL;
	DRAW* drawer = NULL;
};

