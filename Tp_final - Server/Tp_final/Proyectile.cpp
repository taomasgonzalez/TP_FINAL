#include "Proyectile.h"
#include "ProyectilesActionsFSM.h"


Proyectile::Proyectile(unsigned int id, Sense_type proyectile_sense) : MapThing(id, false, proyectile_sense)
{
	moving_timer = al_create_timer(1.0);
	ProyectilesActionsFSM* fsm = new ProyectilesActionsFSM(this);
	EventGenerator* ev_gen = new EventGenerator();
	ev_handler = new EventHandler(fsm, ev_gen);
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



