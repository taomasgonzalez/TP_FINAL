#pragma once
#include "LogicServerFSM.h"
#include "LogicClientFSM.h"

class FSMFactory
{
	enum class FSM_type{Server, Client, Graphic};
public:
	FSMFactory();
	~FSMFactory();

	FSM* create_fsm(FSM_type identifyer, Userdata * data);
};

