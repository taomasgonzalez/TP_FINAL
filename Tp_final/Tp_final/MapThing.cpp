#include "MapThing.h"

MapThing::MapThing(unsigned int id, bool is_nothing)
{
	this->id = id;
	if (is_nothing)
		printable = 'E';		//thing vacio
	else
		printable = 'F';		//es pared
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
bool MapThing::is_floor() {
	return (printable == 'F');
}

bool MapThing::is_player() {
	return false;
}

Thing_Type MapThing::get_map_thing_type()
{
	if(is_enemy()) return Thing_Type::ENEMY;
	else if(is_player()) return Thing_Type::PLAYER;
	else if(is_proyectile()) return Thing_Type::PROYECTILE;
	else if (is_floor()) return Thing_Type::FLOOR;

}

void MapThing::set_printable(char printable)
{
	this->printable = printable;
}

char MapThing::get_printable()
{
	return printable;
}
