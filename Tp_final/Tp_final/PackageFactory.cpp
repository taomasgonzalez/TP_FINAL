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
		pac = new NAME_IS_package(((NAME_IS_EventPackage *)info_received)->give_me_your_name_length(), ((NAME_IS_EventPackage *)info_received)->give_me_your_name());
		break;

	case Event_type::MAP_IS:
		pac = new MAP_IS_package(((MAP_IS_EventPackage *)info_received)->give_me_the_map());
		break;

	case Event_type::GAME_START:
		pac = new GAME_START_package();
		break;

	case Event_type::LOCAL_ACTION_ACCEPTED:
		LOCAL_ACTION_ACCEPTED_EventPackage * info_to_be_send = (LOCAL_ACTION_ACCEPTED_EventPackage *)info_received;
		if (info_to_be_send->give_me_the_move() == Action_type::Move)
			pac = new MOVE_package(info_to_be_send->give_me_the_character(), info_to_be_send->give_me_the_fil_de(), info_to_be_send->give_me_the_col_de());
		else
			pac = new ATTACK_package(info_to_be_send->give_me_the_character(), info_to_be_send->give_me_the_fil_de(), info_to_be_send->give_me_the_col_de());
		break;

	case Event_type::ACTION_REQUEST_ACCEPTED:

		pac = new ACTION_REQUEST_package(((ACTION_REQUEST_ACCEPTED_EventPackage *)info_to_be_send)->give_me_the_move(), ((ACTION_REQUEST_ACCEPTED_EventPackage *)info_to_be_send)->give_me_the_fil_de(), ((ACTION_REQUEST_ACCEPTED_EventPackage *)info_to_be_send)->give_me_the_col_de());
		
		break;

	case Event_type::LOCAL_ENEMY_ACTION:

		pac = new ENEMY_ACTION_package(((LOCAL_ENEMY_ACTION_EventPackage*)info_to_be_send)->give_me_the_monsterID(),((LOCAL_ENEMY_ACTION_EventPackage *)info_to_be_send)->give_me_the_action(), ((LOCAL_ENEMY_ACTION_EventPackage *)info_to_be_send)->give_me_the_destination_row(), ((LOCAL_ENEMY_ACTION_EventPackage *)info_to_be_send)->give_me_the_destination_column());

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

	case Event_type::LOCAL_ERROR:
		pac = new ERROR_package();
		break;

	case Event_type::LOCAL_QUIT:
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
		 my_event_package = new EXTERN_ACTION_RECEIVED_EventPackage(Action_type::Move, ((MOVE_package *)package_recieved)->give_me_the_character(), ((MOVE_package *)package_recieved)->give_me_the_destination_row, ((MOVE_package *)package_recieved)->give_me_the_destination_column()); //soy cliente y me llega un MOVE del servidor
		 break;

	 case Package_type::ATTACK: //soy cliente y me llega un ATTACK del servidor
		 my_event_package = new EXTERN_ACTION_RECEIVED_EventPackage(Action_type::Attack, ((ATTACK_package *)package_recieved)->give_me_the_character(), ((ATTACK_package *)package_recieved)->give_me_the_destination_row, ((ATTACK_package *)package_recieved)->give_me_the_destination_column()); //soy cliente y me llega un MOVE del servidor
		 break;

	 case Package_type::ACTION_REQUEST:  //soy servidor y me llega un ACTION_REQUEST del cliente

		 my_event_package->ev = Event_type::EXTERN_ACTION_REQUESTED;
		 my_event_package->my_info->action = ((ACTION_REQUEST_package *)package_recieved)->give_me_the_action();
		 my_event_package->my_info->destination_row = ((ACTION_REQUEST_package *)package_recieved)->give_me_the_destination_row();
		 my_event_package->my_info->destination_col = ((ACTION_REQUEST_package *)package_recieved)->give_me_the_destination_column();
		 break;

	 case Package_type::ENEMY_ACTION:
		 my_event_package->ev = Event_type::EXTERN_ACTION_RECEIVED;
		 my_event_package->my_info->MonsterID = ((ENEMY_ACTION_package *)package_recieved)->give_me_the_monsterID();
		 my_event_package->my_info->action = ((ENEMY_ACTION_package *)package_recieved)->give_me_the_action();
		 my_event_package->my_info->destination_row = ((ENEMY_ACTION_package *)package_recieved)->give_me_the_destination_row();
		 my_event_package->my_info->destination_col = ((ENEMY_ACTION_package *)package_recieved)->give_me_the_destination_column();
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

	 
