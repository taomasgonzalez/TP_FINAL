#include "PackageFactory.h"



PackageFactory::PackageFactory()
{
}

 Package * PackageFactory::create_package(PackageInfo* info_to_be_send)
{
	Package * pac=NULL;

	switch (info_to_be_send->header)
	{
	case Package_type::ACK:
		pac = new Package(Package_type::ACK);
		break;

	case Package_type::NAME:
		pac = new Package(Package_type::NAME);
		break;

	case Package_type::NAME_IS:
		uchar name_length = PackageFactory::give_me_name_length(info_to_be_send->Name);
		pac = new NAME_IS_package( name_length, info_to_be_send->Name);
		break;

	case Package_type::MAP_IS:
		pac = new MAP_IS_package( info_to_be_send->map);
		break;

	case Package_type::GAME_START:
		pac = new Package(Package_type::GAME_START);
		break;

	case Package_type::MOVE:
		pac = new MOVE_package(info_to_be_send->character, info_to_be_send->destination_row, info_to_be_send->destination_col);

		break;

	case Package_type::ATTACK:
		pac = new ATTACK_package(info_to_be_send->character, info_to_be_send->destination_row, info_to_be_send->destination_col);
		break;

	case Package_type::ACTION_REQUEST:
		pac = new ACTION_REQUEST_package(info_to_be_send->action, info_to_be_send->destination_row, info_to_be_send->destination_col);
		break;

	case Package_type::ENEMY_ACTION:
		pac = new ENEMY_ACTION_package(info_to_be_send->MonsterID, info_to_be_send->destination_row, info_to_be_send->destination_col);
		break;

	case Package_type::WE_WON:
		pac = new Package(Package_type::WE_WON);
		break;

	case Package_type::PLAY_AGAIN:
		pac = new Package(Package_type::PLAY_AGAIN);
		break;

	case Package_type::GAME_OVER:
		pac = new Package(Package_type::GAME_OVER);
		break;

	case Package_type::ERROR:
		pac = new Package(Package_type::ERROR);
		break;

	case Package_type::QUIT:
		pac = new Package(Package_type::QUIT);
		break;

	}
	
	return pac;
}

 uchar PackageFactory::give_me_name_length(char * my_name)
 {
	 uchar count = 0;
	 for (int i = 0; my_name[i]=!'\0' ; i++)
	 {
		 count++;
	 }

	 return count;
 }

	 
