#include "Proyectile.h"



Proyectile::Proyectile(unsigned int id) : MapThing(id, false)
{
}


Proyectile::~Proyectile()
{
}

bool Proyectile::is_proyectile() {
	return true;
}

bool Proyectile::is_snowball() {
	return false;
}
bool Proyectile::is_fireball() {
	return false;
}