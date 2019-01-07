#pragma once
#include "MapThing.h"

enum class States
{
	Moving, Frozen
};
class Character: public MapThing
{
public:
	Character();
	~Character();

	unsigned int pos_x;
	unsigned int pos_y;
	States current_state;
	//Observer_dibujo
};

