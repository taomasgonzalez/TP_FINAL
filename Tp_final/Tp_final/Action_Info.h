#include "Userdata.h"

enum class Event_type;
struct Action_info {

	Event_type my_info_header;
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

