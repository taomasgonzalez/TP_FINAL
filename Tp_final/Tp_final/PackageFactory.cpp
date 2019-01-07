#include "PackageFactory.h"



PackageFactory::PackageFactory()
{
}

Package * PackageFactory::create_package(Package_type my_package_type, EventPackage * EP_to_be_send)
{
	Package * pac;
	Event my_ev = EP_to_be_send->ev;

	if(my_package_type!= Package_type::ATTACK|| Package_type::ATTACK)
	switch (my_ev)
	{
	case Event::ACK:
		pac = new ACK_package;
		break;
	case Event::LOCAL_QUIT:
		pac = new QUIT_package;
		break;
	case Event::EXTERN_QUIT:
		break;
	case Event::LOCAL_ACTION:
		break;
	case Event::EXTERN_ACTION_RECEIVED:
		break;
	case Event::EXTERN_ACTION_REQUESTED:
		break;
	case Event::EXTERN_ACTION_DENIED:
		break;
	case Event::EXTERN_ACTION_ACCEPTED:
		break;
	case Event::EXTERN_ERROR:
		break;
	case Event::LOCAL_ERROR:
		break;
	case Event::NAME_IS:
		break;
	case Event::NAME:
		break;
	case Event::MAP_IS:
		break;
	case Event::MAP_IS_OK:
		break;
	case Event::ENEMY_ACTION:
		break;
	case Event::ENEMY_ACTION_IS_OK:
		break;
	case Event::GAME_START:
		break;
	case Event::START_COMMUNICATION:
		break;
	case Event::NO_EVENT:
		break;
	default:
		break;
	}
	
	return nullptr;
}


