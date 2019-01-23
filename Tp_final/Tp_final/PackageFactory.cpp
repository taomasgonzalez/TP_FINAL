#include "PackageFactory.h"



PackageFactory::PackageFactory()
{
}

 Package * PackageFactory::event_package_2_package(EventPackage* info_received)
{
	Package * pac=NULL;

	switch (info_received->give_me_your_event_type())
	{
	case Event_type::ACK:
		pac = new ACK_package();
		break;

	case Event_type::NAME:
		pac = new NAME_package();
		break;

	case Event_type::NAME_IS:
		pac = new NAME_IS_package(((NAME_IS_EventPackage *)info_received)->get_name_lenght(), ((NAME_IS_EventPackage *)info_received)->give_me_your_name());
		break;

	case Event_type::MAP_IS:
		pac = new MAP_IS_package(((MAP_IS_EventPackage *)info_received)->give_me_the_map());
		break;

	case Event_type::GAME_START:
		pac = new GAME_START_package();
		break;

	case Event_type::MOVE:
			pac = new MOVE_package(((MOVE_EventPackage *)info_received)->give_me_the_character(), ((MOVE_EventPackage *)info_received)->give_me_the_destination_row(), ((MOVE_EventPackage *)info_received)->give_me_the_destination_column());
		break;

	case Event_type::ATTACK:
		pac = new ATTACK_package(((ATTACK_package *)info_received)->give_me_the_character(), ((ATTACK_package *)info_received)->give_me_the_destination_row(), ((ATTACK_package *)info_received)->give_me_the_destination_column());

		break;

	case Event_type::ACTION_REQUEST:
		pac = new ACTION_REQUEST_package(((ACTION_REQUEST_package *)info_received)->give_me_the_action(), ((ACTION_REQUEST_package *)info_received)->give_me_the_destination_row(), ((ACTION_REQUEST_package *)info_received)->give_me_the_destination_column());		
		break;

	case Event_type::ENEMY_ACTION:

		pac = new ENEMY_ACTION_package(((ENEMY_ACTION_EventPackage*)info_received)->give_me_the_monsterID(),((ENEMY_ACTION_EventPackage *)info_received)->give_me_the_action(), ((ENEMY_ACTION_EventPackage *)info_received)->give_me_the_destination_row(), ((ENEMY_ACTION_EventPackage *)info_received)->give_me_the_destination_column());

		break;

	case Event_type::WE_WON:
		pac = new WE_WON_package();
		break;

	case Event_type::PLAY_AGAIN:
		pac = new PLAY_AGAIN_package();
		break;

	case Event_type::GAME_OVER:
		pac = new GAME_OVER_package();
		break;

	case Event_type::ERROR1:
		pac = new ERROR_package();
		break;

	case Event_type::QUIT:
		pac = new QUIT_package();
		break;

	}
	
	return pac;
}


 EventPackage * PackageFactory::package_2_event_package(Package * package_recieved)
 {
	 EventPackage * my_event_package = NULL;

	 switch (package_recieved->get_package_header()) //COMPROBAR QUE FUNCIONA 
	 {
	 case Package_type::ACK:
		 my_event_package = new ACK_EventPackage();
		 break;

	 case Package_type::NAME:
		 my_event_package= new NAME_EventPackage();
		 break;

	 case Package_type::NAME_IS:
		 my_event_package = new EXTERN_NAME_IS_EventPackage(((NAME_IS_package *)package_recieved)->give_me_your_name());
		 break;

	 case Package_type::MAP_IS:
		 my_event_package = new MAP_IS_EventPackage(((MAP_IS_package *)package_recieved)->give_me_the_map());
		 break;

	 case Package_type::GAME_START:
		 my_event_package = new GAME_START_EventPackage();
		 break;

	 case Package_type::MOVE:  //soy cliente y me llega un MOVE del servidor
		 my_event_package = new EXTERN_ACTION_RECEIVED_EventPackage(Action_type::Move, ((MOVE_package *)package_recieved)->give_me_the_character(), ((MOVE_package *)package_recieved)->give_me_the_destination_row, ((MOVE_package *)package_recieved)->give_me_the_destination_column()); 
		 break;

	 case Package_type::ATTACK: //soy cliente y me llega un ATTACK del servidor
		 my_event_package = new EXTERN_ACTION_RECEIVED_EventPackage(Action_type::Attack, ((ATTACK_package *)package_recieved)->give_me_the_character(), ((ATTACK_package *)package_recieved)->give_me_the_destination_row, ((ATTACK_package *)package_recieved)->give_me_the_destination_column()); 
		 break;

	 case Package_type::ACTION_REQUEST:  //soy servidor y me llega un ACTION_REQUEST del cliente
		 my_event_package = new ACTION_REQUEST_RECIEVED_EventPackage( ((ACTION_REQUEST_package *)package_recieved)->give_me_the_action(), ((ACTION_REQUEST_package *)package_recieved)->give_me_the_destination_row, ((ACTION_REQUEST_package *)package_recieved)->give_me_the_destination_column()); 
		 break;

	 case Package_type::ENEMY_ACTION:
		 my_event_package = new EXTERN_ENEMY_ACTION_EventPackage(((ENEMY_ACTION_package *)package_recieved)->give_me_the_monsterID(), ((ENEMY_ACTION_package *)package_recieved)->give_me_the_action(), ((ENEMY_ACTION_package *)package_recieved)->give_me_the_destination_row, ((ENEMY_ACTION_package *)package_recieved)->give_me_the_destination_column());
		 break;

	 case Package_type::WE_WON:
		 my_event_package = new WE_WON_EventPackage();
		 break;

	 case Package_type::PLAY_AGAIN:
		 my_event_package = new PLAY_AGAIN_EventPackage();
		 break;

	 case Package_type::GAME_OVER:
		 my_event_package = new GAME_OVER_EventPackage();
		 break;

	 case Package_type::ERROR1:
		 my_event_package = new EXTERN_ERROR_EventPackage();
		 break;

	 case Package_type::QUIT:
		 my_event_package = new EXTERN_QUIT_EventPackage();
		 break;

	 }

	 return my_event_package;
 }

	 
