#pragma once
#include "Observer.h"
#include "GraphicProyectileFSM.h"
#include "DRAW.h"

class ProyectileFSMDrawerObserver
{
public:
	ProyectileFSMDrawerObserver(GraphicProyectileFSM* fsm, DRAW* drawer);
	~ProyectileFSMDrawerObserver();

	void update();
private:
	GraphicProyectileFSM * fsm;
	DRAW* drawer;
};

