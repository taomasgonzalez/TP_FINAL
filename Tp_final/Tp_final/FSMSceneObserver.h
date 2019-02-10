#pragma once
#include "Observer.h"
#include "LogicFSM.h"
#include "Scene.h"
#include "LogicEventGenerator.h"
#include "EventHandler.h"
#include "EventPackage.h"
#include "Userdata.h"
#include "EventPackageFactory.h"


class FSMSceneObserver: public Observer
{
public:
	FSMSceneObserver(LogicFSM* fsm, Scene *scenario, LogicEventGenerator *event_gen,Userdata * data);
	~FSMSceneObserver();

	virtual void update();

private:
	LogicFSM * my_fsm;
	Scene * my_scenario;
	LogicEventGenerator * my_event_gen;
	Userdata* my_user_data;
};