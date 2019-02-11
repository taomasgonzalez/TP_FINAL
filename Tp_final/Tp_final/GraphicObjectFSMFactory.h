#pragma once
#include "GraphicObjectFSM.h"

#include "Userdata.h"

class GraphicObjectFSMFactory
{
public:
	GraphicObjectFSMFactory(Userdata* data);
	~GraphicObjectFSMFactory();

	GraphicObjectFSM * create_graphic_object(Item_type identifyer, unsigned int id);
	void append_graphic_facility(void *drawer);

private:
	DRAW * drawer = NULL;
	Userdata* data;
};

