#pragma once
#include "Observer.h"
#include "MapThingFactory.h"
#include "Userdata.h"
#include "DRAW.h"
class MapThingFactoryDRAWObserver:public Observer
{
public:
	MapThingFactoryDRAWObserver(MapThingFactory* factory);
	~MapThingFactoryDRAWObserver();

	void update();
private:
	MapThingFactory * factory = NULL;
	DRAW * drawer = NULL;
};


