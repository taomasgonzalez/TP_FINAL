#pragma once
#include "EventGenerator.h"

using namespace std;

class MapThingEventGenerator : public EventGenerator
{
public:
	enum class MapThing_queues { MapThingFSM, Allegro };

	MapThingEventGenerator();
	~MapThingEventGenerator();

protected:
	
};

