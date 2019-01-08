#include "Scene.h"
 
Scene::Scene()
{
	map = new Map(12, 16);
}


Scene::~Scene()
{
	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		delete (*it);
	}
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
		delete (*it);
	}
}

bool Scene::action_is_possible() {
	return false;
}

void Scene::print_current_map() {
	this->map->print_map();
}

void Scene::reset_game()
{
	map->reset_map();
}

void Scene::load_on_map(char * map_string)
{
	map->load_on_map(map_string);
}
