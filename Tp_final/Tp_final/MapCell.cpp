#include "MapCell.h"



MapCell::MapCell()
{
}


MapCell::~MapCell()
{
}
bool MapCell::has_enemies() {

	for (std::vector<MapThing*>::iterator it = cell_things.begin(); it != cell_things.end(); ++it) {
		if ((*it)->is_enemy())
			return true;
	}
	return false;
}
std::vector<MapThing*> MapCell::get_enemies() {

	for (std::vector<MapThing*>::iterator it = cell_things.begin(); it != cell_things.end(); ++it) {
		if ((*it)->is_enemy())
			return true;
	}
	return false;
}
bool MapCell::has_players() {

	for (std::vector<MapThing*>::iterator it = cell_things.begin(); it != cell_things.end(); ++it) {
		if ((*it)->is_player())
			return true;
	}
	return false;
}
bool MapCell::has_proyectiles() {

	for (std::vector<MapThing*>::iterator it = cell_things.begin(); it != cell_things.end(); ++it) {
		if ((*it)->is_proyectile())
			return true;
	}
	return false;
}
