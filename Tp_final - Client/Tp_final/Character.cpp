#include "Character.h"

Character::Character(unsigned int id, Sense_type sense) : MapThing(id, false, sense)
{

}


Character::~Character()
{
}

void Character::die()
{
	dead = true;
}

bool Character::is_dead()
{
	return dead;
}


void Character::append_action_to_character(Action_info action) {

	EventPackage* ev_pack = NULL;
	if (action.action == Action_type::Attack)
		ev_pack = new ATTACK_EventPackage();

	else if (action.action == Action_type::Move) {
		switch (action.my_direction) {
		case Direction_type::Jump_Right:
		case Direction_type::Jump_Left:
			ev_pack = new JUMPED_FORWARD_EventPackage(action.my_direction);
			break;
		case Direction_type::Jump_Straight:
			ev_pack = new JUMPED_EventPackage();
			break;
		case Direction_type::Left:
		case Direction_type::Right:
			ev_pack = new WALKED_EventPackage(action.my_direction);
			break;
		}
	}
	ev_handler->get_ev_gen()->append_new_event(ev_pack, 0);
}
