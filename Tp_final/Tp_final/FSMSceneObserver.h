#pragma once
#include "Observer.h"
#include "FSM_Class.h"
#include "Scene.h"

class FSMSceneObserver: public Observer
{
public:
	FSMSceneObserver(Fsm* fsm, Scene *scenario);
	~FSMSceneObserver();

	virtual void update();

private:
	Fsm * fsm;
	Scene * scenario;
};