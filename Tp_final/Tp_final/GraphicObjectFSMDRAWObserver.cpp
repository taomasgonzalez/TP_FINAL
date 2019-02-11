#include "GraphicObjectFSMDRAWObserver.h"

GraphicObjectFSMDRAWObserver::GraphicObjectFSMDRAWObserver(GraphicObjectFSM * fsm, DRAW * drawer)
{
	this->fsm = fsm;
	this->drawer = drawer;
}

GraphicObjectFSMDRAWObserver::~GraphicObjectFSMDRAWObserver()
{
}


void GraphicObjectFSMDRAWObserver::update() {

}