#pragma once
#include "Observer.h"
#include "FSM_Class.h"
#include "Scene.h"
#include "EventGenerator.h"


class FSMSceneObserver: public Observer
{
public:
	FSMSceneObserver(FSM* fsm, Scene *scenario);
	~FSMSceneObserver();

	virtual void update();

private:
	FSM * fsm;
	Scene * scenario;
};