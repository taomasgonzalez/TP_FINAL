#pragma once
#include "Observer.h"
#include "GraphicCharacterFSM.h"
#include "DRAW.h"

class CharacterFSMDrawerObserver : public Observer
{
public:
	CharacterFSMDrawerObserver(GraphicCharacterFSM* fsm, DRAW* drawer);
	~CharacterFSMDrawerObserver();

	void update();
private:
	GraphicCharacterFSM * fsm;
	DRAW* drawer;
};

