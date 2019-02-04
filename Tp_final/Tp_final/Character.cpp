#include "Character.h"



Character::Character(unsigned int id) : MapThing(id, false)
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


