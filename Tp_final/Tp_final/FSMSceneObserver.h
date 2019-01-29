#pragma once
#include "Observer.h"
#include "FSM_Class.h"
#include "Scene.h"
#include "EventGenerator.h"
#include "EventHandler.h"
#include "EventPackage.h"
#include "Userdata.h"



class FSMSceneObserver: public Observer
{
public:
	FSMSceneObserver(FSM* fsm, Scene *scenario, EventGenerator *event_gen,Userdata * data);
	~FSMSceneObserver();

	virtual void update();

private:
	FSM * my_fsm;
	Scene * my_scenario;
	EventGenerator * my_event_gen;
	Userdata* my_user_data;
};