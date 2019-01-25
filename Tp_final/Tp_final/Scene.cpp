#include "Scene.h"
 
Scene::Scene():Observable(Observable_type::SCENARIO)
{
	this->game_finished = false;
	this->game_started = false;
	this->check_action = false;		//see where this flag is turn on or off
	this->has_to_draw = false;
	

	load_maps(); //levanto los CVS, construyo los mapas y los cargo en el vector
}


Scene::~Scene()
{

	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
		delete (*it);
	}
}



void Scene::handle_movement(Character_id char_id, unsigned int id, Direction_type dir, Action_type action) {
	
}



void Scene::load_maps() {

	//load_vectors with txt
	//this->actual_map = maps.begin();  //asign iterator to the first map
	this->actual_map = 1;

}

void Scene::gameInit() {	

	this->game_started = true;	//indica que todo inicializo correctamente y entonces debe empezar a funcionar la FSM.
	notify_obs();
	this->game_started = false;

}

bool Scene::should_init() {

	return this->game_started;
}


bool Scene::game_is_finished() {
	return this->game_finished;
}
void Scene::finish_game() {
	this->game_finished = true;
}

bool Scene::is_the_action_possible(Package * package_to_be_analyze) { //analyzation of the current package from networking to check if it is a valid action

	bool is_the_action_possible = true;

	//analysis

	if (is_the_action_possible)
		this->package_to_be_appended = package_to_be_analyze;


	return is_the_action_possible;
}

bool Scene::should_the_action_be_checked()
{
	
	return this->check_action;
}

EventPackage * Scene::give_me_my_checked_package()
{
	//analizar y cambiar valid_action en los paquetes
	
	return this->package_to_be_appended;
}

bool Scene::do_you_have_to_draw() {

	return this->has_to_draw;
}


