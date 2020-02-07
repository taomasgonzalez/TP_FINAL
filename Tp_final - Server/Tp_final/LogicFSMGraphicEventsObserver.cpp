#include "LogicFSMGraphicEventsObserver.h"



LogicFSMGraphicEventsObserver::LogicFSMGraphicEventsObserver(LogicFSM* logic, GraphicEventGenerator* graphic)
{
	this->logic = logic;
	this->graphic = graphic;
}


LogicFSMGraphicEventsObserver::~LogicFSMGraphicEventsObserver()
{
}

void LogicFSMGraphicEventsObserver::update() {
	if (logic->start_game) 
		graphic->append_new_event(new GAME_START_EventPackage(true), 0);
}