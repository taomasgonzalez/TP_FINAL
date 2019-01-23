#include "MapCell.h"



MapCell::MapCell()
{
	cell_things = new std::vector<MapThing*>();
}

MapCell::~MapCell()
{
}
bool MapCell::has_enemies() {

	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it) {
		if ((*it)->is_enemy())
			return true;
	}
	return false;
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

	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it) 
		if ((*it)->is_player())
			return true;
	
	return false;
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

	for (std::vector<MapThing*>::iterator it = cell_things->begin(); it != cell_things->end(); ++it)
		if ((*it)->is_proyectile())
			return true;
	
	return false;
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

void MapCell::place_on_cell(MapThing* thing) {
	cell_things->push_back(thing);
}

std::vector<MapThing*> MapCell::get_floors()
{
	return *cell_things;
}

unsigned int MapCell::get_number_of_floors() {
	return (unsigned int)(cell_things->size());
}
