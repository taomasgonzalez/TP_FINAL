#include "Proyectile.h"
#include "ProyectilesActionsEventGenerator.h"
#include "ProyectilesActionsFSM.h"

void get_and_set_timers(ProyectilesActionsEventGenerator* ev_gen, ProyectilesActionsFSM* fsm);

Proyectile::Proyectile(unsigned int id, Sense_type proyectile_sense) : MapThing(id, false, proyectile_sense)
{
	moving_timer = al_create_timer(1.0);
	ProyectilesActionsFSM* fsm = new ProyectilesActionsFSM(this);
	ProyectilesActionsEventGenerator* ev_gen = new ProyectilesActionsEventGenerator(fsm->get_all_timers());
	get_and_set_timers(ev_gen, fsm);
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

FSM * Proyectile::get_my_fsm()
{
	return ev_handler->get_fsm();
}

EventGenerator* Proyectile::get_my_ev_gen() {
	return ev_handler->get_ev_gen();
}


void get_and_set_timers(ProyectilesActionsEventGenerator* ev_gen, ProyectilesActionsFSM* fsm) {
	ev_gen->set_falling_timer(fsm->get_falling_timer());
	ev_gen->set_impacting_timer(fsm->get_impacting_timer());
	ev_gen->set_moving_timer(fsm->get_moving_timer());
}