#pragma once
#include "GraphicObjectFSM.h"
class GraphicCharacterFSM: public GraphicObjectFSM
{
public:

	//deberia tener constructores sobrecargados segun el tipo de jugador y de enemigo!
	GraphicCharacterFSM(Userdata*data, DRAW * drawer, unsigned int id);
	~GraphicCharacterFSM();
	

protected:

};

