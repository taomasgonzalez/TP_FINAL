#include "Character.h"
#include "CharacterActionsFSM.h"
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

bool Character::is_moving()
{
	CharacterActionsFSM* char_fsm =  static_cast<CharacterActionsFSM*>(ev_handler->get_fsm());
	return char_fsm->is_moving();
}

bool Character::is_falling()
{
	CharacterActionsFSM* char_fsm = static_cast<CharacterActionsFSM*>(ev_handler->get_fsm());
	return char_fsm->is_falling();
}

bool Character::is_iddle()
{
	CharacterActionsFSM* char_fsm = static_cast<CharacterActionsFSM*>(ev_handler->get_fsm());
	return char_fsm->is_iddle();
}

bool Character::is_walking()
{
	CharacterActionsFSM* char_fsm = static_cast<CharacterActionsFSM*>(ev_handler->get_fsm());

	return char_fsm->is_walking();
}

Direction_type Character::in_wich_direction_is_the_character_walking()
{
	CharacterActionsFSM* char_fsm = static_cast<CharacterActionsFSM*>(ev_handler->get_fsm());

	return char_fsm->in_wich_direction_is_the_character_walking();
}

bool Character::waiting_for_next_move()
{
	CharacterActionsFSM* char_fsm = static_cast<CharacterActionsFSM*>(ev_handler->get_fsm());

	bool is_pending = char_fsm->obs_info.next_move_pending;

	if (is_pending)
	{
		char_fsm->obs_info.next_move_pending = false;
	}

	return is_pending;
}

bool Character::is_attacking() {
	CharacterActionsFSM* char_fsm = static_cast<CharacterActionsFSM*>(ev_handler->get_fsm());
	return char_fsm->is_attacking();
}

bool Character::has_to_fall()
{
	return static_cast<CharacterActionsFSM*>(ev_handler->get_fsm())->has_to_fall();
}

void Character::dont_fall()
{
	static_cast<CharacterActionsFSM*>(ev_handler->get_fsm())->dont_fall();
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

	if(ev_pack != NULL)
		ev_handler->get_ev_gen()->append_new_event(ev_pack, 0);
}
