#pragma once
#include "Observer.h"
#include "LogicFSM.h"
#include "Scene.h"
#include "LogicEventGenerator.h"
#include "EventHandler.h"
#include "EventPackage.h"
#include "Userdata.h"


class LogicFSMSceneObserver: public Observer
{
public:
	LogicFSMSceneObserver(LogicFSM* fsm, Scene *scenario, LogicEventGenerator *event_gen,Userdata * data);
	~LogicFSMSceneObserver();

	virtual void update();

private:
	LogicFSM * my_fsm;
	Scene * my_scenario;
	LogicEventGenerator * my_event_gen;
	Userdata* my_user_data;
};