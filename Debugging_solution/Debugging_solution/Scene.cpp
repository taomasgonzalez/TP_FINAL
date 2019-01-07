#include "Scene.h"
 
Scene::Scene():Observable()
{
	game_finished = false;
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



void Scene::handle_movement(Character_id char_id, unsigned int id, Direction dir, Action action) {
	
}

void Scene::gameInit(Userdata& Userdata, infoType * mydata) {	

	this->should_init = true;	//indica que todo inicializo correctamente y entonces debe empezar a funcionar la FSM.
	notify_obs();
}

bool Scene::game_is_finished() {
	return game_finished;
}
void Scene::finish_game() {
	game_finished = true;
}

bool Scene::action_is_possible() {

}


bool Scene::game_finished = false;