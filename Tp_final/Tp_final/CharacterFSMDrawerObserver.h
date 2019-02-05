#pragma once
#include "Observer.h"
#include "GraphicCharacterFSM.h"
#include "Drawer.h"

class CharacterFSMDrawerObserver : public Observer
{
public:
	CharacterFSMDrawerObserver(GraphicCharacterFSM* fsm, Drawer* drawer);
	~CharacterFSMDrawerObserver();

	void update();
private:
	GraphicCharacterFSM * fsm;
	Drawer* drawer;
};

