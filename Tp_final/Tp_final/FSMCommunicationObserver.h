#pragma once
#include "Communication.h"
#include "FSM_Class.h"
#include "Scene.h"
#include "PackageFactory.h"
#include "EventGenerator.h"

class FSMCommunicationObserver: public Observer
{
public:
	FSMCommunicationObserver(FSM * fsm, Communication * com, Scene* scenario);
	~FSMCommunicationObserver();

	virtual void update();
private:
	FSM * fsm;
	Communication * com;
	Scene * scenario;
};


