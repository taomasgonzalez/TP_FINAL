#include "Scene.h"
 
Scene::Scene():Observable(Observable_type::SCENARIO)
{
	this->game_finished = false;
	this->should_init = false;
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



void Scene::handle_movement(Character_id char_id, unsigned int id, Direction dir, Action_type action) {
	
}

char * Scene::give_me_the_original_map()
{
	return this->original_map_distribution;
}

void Scene::gameInit(Userdata& Userdata) {	

	this->should_init = true;	//indica que todo inicializo correctamente y entonces debe empezar a funcionar la FSM.
	notify_obs();
}

bool Scene::game_is_finished() {
	return game_finished;
}
void Scene::finish_game() {
	game_finished = true;
}

bool Scene::action_is_possible(EventPackage * package_to_be_analyze) { //analyzation of the current eventpackage to check if it is a valid action

	bool is_the_action_possible = true;

	//analysis

	if (is_the_action_possible)
		this->package_to_be_appended = package_to_be_analyze;
	else
		int i; //send an error EventPackage

	return is_the_action_possible;
}

bool Scene::should_the_action_be_checked()
{
	
	return this->check_action;
}

EventPackage * Scene::give_me_my_checked_package()
{
	return this->package_to_be_appended;
}


bool Scene::game_finished = false;