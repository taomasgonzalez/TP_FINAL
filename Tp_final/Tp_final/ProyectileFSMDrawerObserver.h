#pragma once
#include "Observer.h"
#include "GraphicProyectileFSM.h"
#include "Drawer.h"

class ProyectileFSMDrawerObserver
{
public:
	ProyectileFSMDrawerObserver(GraphicProyectileFSM* fsm, Drawer* drawer);
	~ProyectileFSMDrawerObserver();

	void update();
private:
	GraphicProyectileFSM * fsm;
	Drawer* drawer;
};

