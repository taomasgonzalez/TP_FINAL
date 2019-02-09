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


