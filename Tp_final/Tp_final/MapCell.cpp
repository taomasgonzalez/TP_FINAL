#include "MapCell.h"

MapCell::MapCell()
{
	cell_things = new std::vector<MapThing*>();
}

MapCell::~MapCell()
{
}
bool MapCell::has_enemies() {
	return i_have_enemies;
}

//debe ser llamada has_enemies previamente!!!
std::vector<Enemy*> MapCell::get_enemies() {
	std::vector<Enemy*> enemigos = std::vector<Enemy*>();
	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it) {
		if ((*it)->is_enemy())
			enemigos.push_back((Enemy*)(*it));
	}
	return enemigos;
}
bool MapCell::has_players() {
	return i_have_players;
}
//debe ser llamada has_players previamente!!!
std::vector<Player*> MapCell::get_players() {
	std::vector<Player*> amigos = std::vector<Player*>();
	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it)
		if ((*it)->is_player())
			amigos.push_back((Player*)(*it));

	return amigos;
}

bool MapCell::has_proyectiles() {
	return i_have_proyectiles;
}
//debe ser llamada has_proyectiles previamente!!!
std::vector<Proyectile*> MapCell::get_proyectiles() {
	std::vector<Proyectile*> proy = std::vector<Proyectile*>();
	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it)
		if ((*it)->is_proyectile())
			proy.push_back((Proyectile*)(*it));

	return proy;
}

//devuelve null en caso de que no este el id deseado
MapThing* MapCell::get_id(unsigned int wanted_id) {
	MapThing * found_id = NULL;
	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it)
		if ((*it)->id == wanted_id)
			found_id = (*it);

	return found_id;
}

bool MapCell::delete_id(unsigned int wanted_id) {
	bool successfully_deleted = false;
	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it) {
		if ((*it)->id == wanted_id) {
			successfully_deleted = true;
			cell_things->erase(it);
			break;
		}
	}
	return successfully_deleted;
}

bool MapCell::delete_map_thing(MapThing * thing)
{
	bool successfully_deleted = false;

	//does the deletion and sets the according i_have variable to false, so that it may be updated more easily afterwards. 
	Thing_Type deleted_type = thing->get_map_thing_type();
	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it) 
		if ((*it) == thing) {
			successfully_deleted = true;
			cell_things->erase(it);
			set_i_have_variable(deleted_type, false);
			break;
		}
	
	//updates the value of the i_have variables according to the new state of the cell after the deletion.
	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it) 
		if((*it)->get_map_thing_type() == deleted_type){
			set_i_have_variable(deleted_type, true);
			break;
		}
	
	return successfully_deleted;
}

void MapCell::place_on_cell(MapThing* thing) {

	if (thing->is_proyectile())
		i_have_proyectiles = true;
	else if (thing->is_enemy())
		i_have_enemies = true;
	else if (thing->is_player())
		i_have_players = true;

	cell_things->push_back(thing);
}

std::vector<MapThing*> MapCell::get_floors()
{
	return *cell_things;
}

unsigned int MapCell::get_number_of_floors() {
	return (unsigned int)(cell_things->size());
}

MapThing * MapCell::get_floor(int floor_number)
{
	return (*cell_things)[floor_number];
}

void MapCell::print() {
	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it) {
		printf("%c", (*it)->get_printable());
	}
}

void MapCell::clear() {
	cell_things->clear();
}

void MapCell::set_i_have_variable(Thing_Type type,bool set_to) {
	if (type == Thing_Type::PROYECTILE)
		i_have_proyectiles = set_to;
	else if (type == Thing_Type::ENEMY)
		i_have_enemies = set_to;
	else if (type == Thing_Type::PLAYER)
		i_have_players = set_to;
}