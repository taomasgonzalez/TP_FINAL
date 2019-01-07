#pragma once
#include "Communication.h"
#include "FSM_Class.h"

class FSMCommunicationObserver: public Observer
{
public:
	FSMCommunicationObserver(Fsm * fsm, Communication * com);
	~FSMCommunicationObserver();

	virtual void update();
private:
	Fsm * fsm;
	Communication * com;
};

