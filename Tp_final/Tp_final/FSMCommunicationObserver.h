#pragma once
#include "Observer.h"
#include "Communication.h"
#include "FSM_Class.h"
#include "Scene.h"
#include "PackageFactory.h"
#include "EventGenerator.h"
#include "EventPackage.h"
#include "EventHandler.h"



class FSMCommunicationObserver: public Observer
{
public:
	FSMCommunicationObserver(FSM * fsm, Communication * com, Scene* scenario, Userdata * data);
	~FSMCommunicationObserver();

	virtual void update();
private:
	FSM * fsm;
	Communication * com;
	Scene * scenario;
	Userdata * my_user_data;
};


