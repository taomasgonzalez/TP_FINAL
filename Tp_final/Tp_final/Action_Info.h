#pragma once
#include "Userdata.h"

enum class Action_info_id{ MOVE, ATTACK, ACTION_REQUEST, ENEMY_ACTION, None};
struct Action_info {

	Action_info_id my_info_header;
	bool is_local;
	bool finished_loading; //For ENEMYS_LOADED_EventPackage
	unsigned int id;
	int final_pos_x;
	int final_pos_y;
	Action_type action;
	Direction_type my_direction;
	Item_type my_character;
	bool valid = false;
};

