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
			break;
		case FSM_type::Client:
			new_born = new LogicClientFSM(data);
			break;
		case FSM_type::Graphic_Game:
			new_born = new GraphicGameFSM(drawer);
			break;
	}
	return new_born;
}

void FSMFactory::append_drawing_facility(DRAW* drawer) {
	this->drawer = drawer;
}
void FSMFactory::append_data_facility(Userdata* data) {
	this->data = data;
}