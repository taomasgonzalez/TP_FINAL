#pragma once
#include "GraphicObjectFSM.h"
#include "DRAW.h"
#include "Observer.h"

class GraphicObjectFSMDRAWObserver:public Observer
{
public:
	GraphicObjectFSMDRAWObserver(GraphicObjectFSM* fsm, DRAW* drawer);

	~GraphicObjectFSMDRAWObserver();

	void update();

private:
	GraphicObjectFSM* fsm = NULL;
	DRAW* drawer = NULL;
};

