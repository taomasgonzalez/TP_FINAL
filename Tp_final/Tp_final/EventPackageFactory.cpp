#include "EventPackageFactory.h"



EventPackageFactory::EventPackageFactory()
{
}


EventPackageFactory::~EventPackageFactory()
{
}

EventPackage* create_event_package(Action_info * create_from) {

	EventPackage* my_checked_event = NULL;
	switch (create_from->my_info_header)
	{

	case Action_info_id::MOVE:
		my_checked_event = new MOVE_EventPackage(create_from);

		break;
	case Action_info_id::ATTACK:
		my_checked_event = new ATTACK_EventPackage(create_from);

		break;
	case Action_info_id::ACTION_REQUEST:
		my_checked_event = new ACTION_REQUEST_EventPackage(create_from);

		break;

	case Action_info_id::ENEMY_ACTION:
		my_checked_event = new ENEMY_ACTION_EventPackage(create_from);

		break;

	}
	return my_checked_event;
}