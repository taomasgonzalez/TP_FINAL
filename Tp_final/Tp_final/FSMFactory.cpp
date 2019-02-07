#include "FSMFactory.h"



FSMFactory::FSMFactory()
{
}


FSMFactory::~FSMFactory()
{
}

FSM * FSMFactory::create_fsm(FSM_type identifyer, Userdata * data)
{
	FSM * new_born = NULL;
	switch (identifyer) {
		case FSM_type::Server:
			new_born = new LogicServerFSM(data);
		case FSM_type::Client:
			new_born = new LogicClientFSM(data);
	}
	return new_born;
}
