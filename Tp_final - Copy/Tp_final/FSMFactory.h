#pragma once
#include "LogicServerFSM.h"
#include "LogicClientFSM.h"
#include "GraphicGameFSM.h"
#include "DRAW.h"

class FSMFactory
{
	enum class FSM_type{Server, Client, Graphic_Game};
public:
	FSMFactory();
	~FSMFactory();

	FSM* create_fsm(FSM_type identifyer, Userdata * data);
	void append_drawing_facility(DRAW* drawer);
	void append_data_facility(Userdata * data);
private:
	DRAW * drawer;
	Userdata * data;
};

