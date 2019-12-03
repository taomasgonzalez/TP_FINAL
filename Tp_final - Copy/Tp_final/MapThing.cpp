#include "MapThing.h"
#include "GraphicEventGenerator.h"

MapThing::MapThing(unsigned int id, bool is_nothing, Sense_type sense)
{
	this->id = id;
	if (is_nothing)
		this->printable = Item_type::NADA;		//thing vacio
	else if(sense==Sense_type::None)
	{
		this->printable = Item_type::FLOOR;		//es pared
		//this->my_sense = Sense_type::None; lo comento porque no le encuentro utilidad para cuando soy un floor pero si me modifica SIEMPRE el sense de todo lo que sea "algo"
	}
	else
		this->my_sense = sense;

	
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
	return (printable == Item_type::FLOOR);
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
	else return Thing_Type::FLOOR;					//este esta de mas, pero es necesario para que siempre se devuelva algo
}

void MapThing::set_printable(Item_type printable)
{
	this->printable = printable;
}

Item_type MapThing::get_printable()
{
	return printable;
}

void MapThing::set_sense(Sense_type sense) {

	this->my_sense = sense;
}
Sense_type MapThing::get_sense() {

	return this->my_sense;
}




