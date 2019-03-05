#include "PackageFactory.h"


EventPackage * PackageFactory::my_event_package = NULL;
Package * PackageFactory::pac = NULL;

PackageFactory::PackageFactory()
{
}

 Package * PackageFactory::event_package_2_package(EventPackage* info_received)
{
	switch (info_received->give_me_your_event_type())
	{
		case Event_type::ACK:
			pac = new ACK_package();
			break;

		case Event_type::NAME:
			pac = new NAME_package();
			break;

		case Event_type::NAME_IS: {
			NAME_IS_EventPackage * info_n = static_cast<NAME_IS_EventPackage*>(info_received);
			pac = new NAME_IS_package(info_n->get_name_lenght(), info_n->give_me_your_name());
		}
			break;

		case Event_type::MAP_IS: {
			MAP_IS_EventPackage * info_m = static_cast<MAP_IS_EventPackage *>(info_received);
			pac = new MAP_IS_package(info_m->give_me_the_map(), info_m->give_me_the_checksum());
		}
			break;

		case Event_type::GAME_START:
			pac = new GAME_START_package();
			break;

		case Event_type::MOVE: {
			MOVE_EventPackage * info_mo = static_cast<MOVE_EventPackage*>(info_received);
			pac = new MOVE_package((Character_type)info_mo->give_me_the_character(), info_mo->give_me_your_destination_row(), info_mo->give_me_your_destination_column());
		}
			break;

		case Event_type::ATTACK: {
			ATTACK_EventPackage * info_a = static_cast<ATTACK_EventPackage*>(info_received);
			pac = new ATTACK_package((Character_type)info_a->give_me_the_character(), info_a->give_me_your_destination_row(), info_a->give_me_your_destination_column());
		}
			break;

		case Event_type::ACTION_REQUEST:{
			ACTION_REQUEST_EventPackage * info_ar = static_cast<ACTION_REQUEST_EventPackage*>(info_received);
			pac = new ACTION_REQUEST_package(info_ar->give_me_the_action(), info_ar->give_me_your_destination_row(), info_ar->give_me_your_destination_column());
		}
			break;

		case Event_type::ENEMY_ACTION: {
			ENEMY_ACTION_EventPackage * info_ea = static_cast<ENEMY_ACTION_EventPackage*>(info_received);
			pac = new ENEMY_ACTION_package(info_ea->give_me_the_monsterID(), info_ea->give_me_the_action(), info_ea->give_me_the_destination_row(), info_ea->give_me_the_destination_column());
		}
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

		case Event_type::LOCAL_QUIT:
			pac = new QUIT_package();
			break;

		default: //me llego un EventPackage corrompido que no se que tiene, cargo un error
			pac = new ERROR_package();
			std::cout << "Me llego un EventPackage con header irrecononocible, en  PackageFactory::event_package_2_package()" << std::endl;
			break;
	}
	
	return pac;
}

 
 EventPackage * PackageFactory::package_2_event_package(Package * package_recieved)
 {

	 switch (package_recieved->get_package_header()) //COMPROBAR QUE FUNCIONA 
	 {
	 case Package_type::ACK:
		 my_event_package = new ACK_EventPackage();
		 break;

	 case Package_type::NAME:
		 std::cout << "me llego un NAME" << std::endl;
		 my_event_package = new NAME_EventPackage();
		 break;

	 case Package_type::NAME_IS: {
		 NAME_IS_package* ni_pack = static_cast<NAME_IS_package*>(package_recieved);
		 my_event_package = new NAME_IS_EventPackage(false, ni_pack->get_name_lenght(), ni_pack->give_me_your_name());
	 }
		break;

	 case Package_type::MAP_IS: {
		 MAP_IS_package* mi_pack = static_cast<MAP_IS_package*>(package_recieved);
		 my_event_package = new MAP_IS_EventPackage(false, mi_pack->give_me_the_map(), mi_pack->give_me_the_checksum());
	 }
		break;

	 case Package_type::GAME_START:
		 my_event_package = new GAME_START_EventPackage();
		 break;

	 case Package_type::MOVE: {  //soy cliente y me llega un MOVE del servidor
		 MOVE_package * mo_pack = static_cast<MOVE_package*>(package_recieved);
		 my_event_package = new MOVE_EventPackage(mo_pack->give_me_the_destination_row(), mo_pack->give_me_the_destination_column());
	 }
	 break;

	 case Package_type::ATTACK: { //soy cliente y me llega un ATTACK del servidor
		 ATTACK_package * a_pack = static_cast<ATTACK_package*>(package_recieved);
		 my_event_package = new ATTACK_EventPackage(a_pack->give_me_the_destination_row(), a_pack->give_me_the_destination_column());
	}
		break;

	 case Package_type::ACTION_REQUEST: {  //soy servidor y me llega un ACTION_REQUEST del cliente
		 ACTION_REQUEST_package * ar_pack = static_cast<ACTION_REQUEST_package*>(package_recieved);
		 my_event_package = new ACTION_REQUEST_EventPackage(ar_pack->give_me_the_action(), ar_pack->give_me_the_destination_row(), ar_pack->give_me_the_destination_column());
	 }
		break;

	 case Package_type::ENEMY_ACTION: {
		 ENEMY_ACTION_package * ea_pack = static_cast<ENEMY_ACTION_package*>(package_recieved);
		 my_event_package = new ENEMY_ACTION_EventPackage(false, ea_pack->give_me_the_monsterID(), ea_pack->give_me_the_action(), ((ENEMY_ACTION_package *)package_recieved)->give_me_the_destination_row(), ((ENEMY_ACTION_package *)package_recieved)->give_me_the_destination_column());
	 }
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
		 my_event_package = new ERROR_EventPackage(false);
		 break;

	 case Package_type::QUIT:
		 my_event_package = new EXTERN_QUIT_EventPackage();
		 break;

	 default: //No puedo reconocer el paquete que llego, implica que está corrompido, se produjo un error de comunicación
		 my_event_package = new ERROR_EventPackage(false);
		 break;
	 }

	 return my_event_package;
 }


	 
