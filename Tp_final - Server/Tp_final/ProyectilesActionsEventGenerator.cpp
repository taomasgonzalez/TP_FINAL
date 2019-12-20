#include "ProyectilesActionsEventGenerator.h"

using namespace std;

ProyectilesActionsEventGenerator::ProyectilesActionsEventGenerator( ) : MapThingEventGenerator()
{

}


ProyectilesActionsEventGenerator::~ProyectilesActionsEventGenerator()
{
}


EventPackage * ProyectilesActionsEventGenerator::fetch_event() {
	update_allegro_timer_events();
	return EventGenerator::fetch_event();
}

void ProyectilesActionsEventGenerator::set_moving_timer(ALLEGRO_TIMER * moving_timer)
{
	this->moving_timer = moving_timer;
}
void ProyectilesActionsEventGenerator::set_falling_timer(ALLEGRO_TIMER * falling_timer)
{
	this->falling_timer = falling_timer;
}
void ProyectilesActionsEventGenerator::set_impacting_timer(ALLEGRO_TIMER* impacting_timer) {
	this->impacting_timer = impacting_timer;
}

void ProyectilesActionsEventGenerator::update_allegro_timer_events() {


}
