#include "Proyectile.h"



Proyectile::Proyectile(unsigned int id, Sense_type proyectile_sense) : MapThing(id, false, proyectile_sense)
{
	moving_timer = al_create_timer(1.0);
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

ALLEGRO_TIMER * Proyectile::get_moving_timer()
{
	return moving_timer;
}
