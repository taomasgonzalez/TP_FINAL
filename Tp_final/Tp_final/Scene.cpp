#include "Scene.h"
 
Scene::Scene():Observable(Observable_type::SCENARIO)
{
	this->game_finished = false;
	this->game_started = false;
	this->check_local_action = false;		
	this->has_to_draw = false;
	this->action_from_allegro = NULL;
	this->actual_map = 1;
	players = new std::vector<Player>();
}


Scene::~Scene()
{
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
		delete (*it);
	}
}



void Scene::handle_movement(Character_id char_id, unsigned int id, Direction_type dir, Action_type action) {
	
}



void Scene::execute_action(EventPackage * action_to_be_executed)
{
}

void Scene::load_new_map(bool is_client, MAP_IS_EventPackage* map_to_be_checked=NULL) {



	if (is_client) //The map came by networking, already checked
	{	
		//esto es lo que tenias antes, que por ahora no se condice con lo que programe de Map. despues coordinar conmigo para que esto funke.
		//Map * new_map = new Map(12, 16, ((MAP_IS_EventPackage*)map_to_be_checked)->give_me_the_map(), ((MAP_IS_EventPackage*)map_to_be_checked)->give_me_the_checksum());
		Map new_map = Map(12, 16);
		new_map.load_on_map((const char*) map_to_be_checked->give_me_the_map());
		
		maps.push_back(new_map);
		
		this->actual_map++;
	}
	else
	{	//I´m server, I´ve the map available
		maps.push_back(new Map(12, 16, give_me_the_CSV(actual_map),this->make_checksum(give_me_the_CSV(actual_map))));
	}


}

//hace checksum , función guido
unsigned char Scene::make_checksum(const char * CSV_map_location) {

	unsigned char local_checksum = 'd';

	return local_checksum;
}//después usar esta función que haga guido para el checksum de mapas que llegan para validarlos(hecho)


bool Scene::is_the_map_okay(EventPackage * map_to_be_checked)
{
	bool map_validation;
	unsigned char extern_checksum = ((MAP_IS_EventPackage *)map_to_be_checked)->give_me_the_checksum();
	unsigned char local_checksum = this->make_checksum(((MAP_IS_EventPackage *)map_to_be_checked)->give_me_the_map());

	if (local_checksum == extern_checksum)
		map_validation = true;
	else
		map_validation = false;
	
	return map_validation;
}

//función que hacce guido, va al archivo, lo convierte a const char* y lo devuelve
const char * Scene::give_me_the_CSV(unsigned int actual_map) {

	const char * prueba=NULL;
	return prueba;
}

void Scene::gameInit() {	

	this->game_started = true;	//indica que todo inicializo correctamente y entonces debe empezar a funcionar la FSM.
	notify_obs();
	this->game_started = false;

}



EventPackage * Scene::give_me_my_allegro_event() {
	return this->action_from_allegro;
}

Character_type Scene::give_me_my_player() {

	return this-> my_player;
}
Character_type Scene::give_the_other_player() {

	return this->other_player;

}

void Scene::set_new_allegro_event(EventPackage * new_event) {
	 this->action_from_allegro= new_event;
}

bool Scene::both_players_dead()
{
	return false;
}

bool Scene::any_monsters_left()
{
	return false;
}


bool Scene::game_is_finished() {
	return this->game_finished;
}

void Scene::finish_game() {
	this->game_finished = true;
	notify_obs();
	this->game_finished = false;
}


//analizo jugadas externas e internas relacionadas a scene
bool Scene::is_the_action_possible(EventPackage * package_to_be_analyze) { 

	bool is_the_action_possible = true;


	//analysis
	is_the_action_possible = check_action(package_to_be_analyze); //función aparte que chequea realemnte para mayor prolijidad
		


	if (is_the_action_possible) //Implementación al pedo por como está hecho en FSMEventsObserver
			package_to_be_analyze->is_this_event_package_is_correct(true);  //valido el EventPackage
	else
			package_to_be_analyze->is_this_event_package_is_correct(false);  //invalido el EventPackage

	return is_the_action_possible;
}

bool Scene::check_action(EventPackage * package_to_be_analyze) {

	//hacer función chequeo
	//unsigned char Map::make_checksum(const char * CSV_map_location) función para chequear el map_is entrante
	return true;
}

bool Scene::did_we_win(EventPackage * package_to_be_analyze)
{
	return false;
}

bool Scene::did_we_lost(EventPackage * package_to_be_analyze)
{
	return false;
}



bool Scene::do_you_have_to_draw() {

	return this->has_to_draw;
}


