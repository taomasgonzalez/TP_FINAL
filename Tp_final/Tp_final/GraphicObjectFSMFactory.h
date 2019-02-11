#pragma once
#include "GraphicObjectFSM.h"

#include "Userdata.h"

class GraphicObjectFSMFactory
{
public:
	GraphicObjectFSMFactory(Userdata* data);
	~GraphicObjectFSMFactory();

	GraphicObjectFSM * create_graphic_object(Item_type identifyer, unsigned int id);

private:
	DRAW * drawer = NULL;
	Userdata* data;
};

