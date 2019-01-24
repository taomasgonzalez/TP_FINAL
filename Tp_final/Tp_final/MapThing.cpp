#include "MapThing.h"



MapThing::MapThing(unsigned int id)
{
	this->id = id;
}


MapThing::MapThing()
{
}

MapThing::~MapThing()
{
}
bool MapThing::is_proyectile() {
	return false;
}
bool MapThing::is_enemy() {
	return false;
}

bool MapThing::is_player() {
	return false;
}