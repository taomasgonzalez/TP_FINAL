#pragma once
#include "Observer.h"
#include "Communication.h"
#include "LogicFSM.h"
#include "Scene.h"
#include "PackageFactory.h"
#include "EventPackage.h"



class FSMCommunicationObserver: public Observer
{
public:
	FSMCommunicationObserver(LogicFSM * fsm, Communication * com, Scene* scenario, Userdata * data);
	~FSMCommunicationObserver();

	virtual void update();
private:
	LogicFSM * fsm;
	Communication * com;
	Scene * scenario;
	Userdata * my_user_data;
};


