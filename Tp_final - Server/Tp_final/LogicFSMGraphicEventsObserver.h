#pragma once

#include "LogicFSM.h"
#include "GraphicEventGenerator.h"

class LogicFSMGraphicEventsObserver : public Observer
{
public:
	LogicFSMGraphicEventsObserver(LogicFSM* logic, GraphicEventGenerator* graphic);
	~LogicFSMGraphicEventsObserver();
	virtual void update();

private:
	LogicFSM * logic = NULL;
	GraphicEventGenerator* graphic = NULL;
};

