#pragma once
#include "EventGenerator.h"

class GraphicEventGenerator: public EventGenerator
{
public:
	GraphicEventGenerator(Allegro * al, Userdata* data);
	~GraphicEventGenerator();
};

