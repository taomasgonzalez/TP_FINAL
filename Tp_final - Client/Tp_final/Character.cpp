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

FSM * Character::get_my_fsm()
{
	return ev_handler->get_fsm();
}

EventGenerator* Character::get_my_ev_gen() {
	return ev_handler->get_ev_gen();
}

