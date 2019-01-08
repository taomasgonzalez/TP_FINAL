#include "PackageInfo.h"



PackageInfo::PackageInfo(Package_type my_header, Scene * escenario, Communication* com, EventPackage* my_event_info)
{
	this->header = my_header;

	switch (my_header)
	{
	case Package_type::NAME_IS:
		this->Name = com->give_me_my_name();
		break;

	case Package_type::MAP_IS:
		this->map = escenario->give_me_the_original_map();
		break;

	case Package_type::MOVE:
	case Package_type::ATTACK:
		this->character = my_event_info->my_character;
		this->destination_row = my_event_info->destiny_position.fil_de;
		this->destination_col = my_event_info->destiny_position.col_de;

		break;

	case Package_type::ACTION_REQUEST:
		this->action = my_event_info->act;
		this->destination_row = my_event_info->destiny_position.fil_de;
		this->destination_col = my_event_info->destiny_position.col_de;
		break;

	case Package_type::ENEMY_ACTION:
		this->MonsterID = my_event_info->action_made_by_id;
		this->action = my_event_info->act;
		this->destination_row = my_event_info->destiny_position.fil_de;
		this->destination_col = my_event_info->destiny_position.col_de;
		break;

	}

}

