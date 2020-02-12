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
	else if (logic->finished_level)
		graphic->append_new_event(new CHANGE_LEVEL_EventPackage(), 0);
	else if (logic->restart_game)
		graphic->append_new_event(new RESTART_GAME_EventPackage(), 0);
	else if (logic->reset_graphic)
		graphic->flush_all_queues();
}