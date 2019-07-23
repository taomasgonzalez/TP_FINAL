#include "Scene.h"
#include "general.h"
#include <fstream>
#include <string>
#include "EnemySceneObserver.h"
#include "PlayerSceneObserver.h"

#define TABLE_FILE "levels/tabla/tabla.csv"
#define FILE_LENGHT (16*12)			// 12 FILAS POR 16 COLUMNAS

const unsigned char *getTable();		// función para obtener la tabla para checksum
 
Scene::Scene(Userdata* data):Observable()
{
	enemy_actions_queue = al_create_event_queue();
	proyectile_actions_queue = al_create_event_queue();
	this->assistant_queue = new std::queue<Action_info>();
	//this->action_from_allegro = NULL;
	this->actual_map = 0;
	enemy_action_info;
	this->data = data;

}


Scene::~Scene()
{
	delete assistant_queue;
}



void Scene::handle_movement(Character_id char_id, unsigned int id, Direction_type dir, Action_type action) {
	
}

void Scene::execute_action(Action_info * action_to_be_executed, bool & should_be_hit)
{

	switch (action_to_be_executed->my_info_header)
	{
	case Action_info_id::MOVE:
		execute_move(action_to_be_executed, should_be_hit);
		break;

	case Action_info_id::ATTACK:
		execute_attack(action_to_be_executed);
		break;

	case Action_info_id::ACTION_REQUEST:

		if (action_to_be_executed->action == Action_type::Move)
			execute_move(action_to_be_executed, should_be_hit);
		else
			execute_attack(action_to_be_executed);

		break;

	case Action_info_id::ENEMY_ACTION:
		execute_enemy_action(action_to_be_executed, should_be_hit);
		break;

	default:
		std::cout << "Error, Acción no ejecutable" << std::endl;
		break;

	}

}

void Scene::execute_proyectile(Proyectile* proyectile_to_be_executed, bool& should_be_hit) {
	
	Proyectile * my_projectile = (Proyectile *)maps[actual_map]->get_from_map(proyectile_to_be_executed->id);

	if (proyectile_to_be_executed->is_fireball())
	{
		if (maps[actual_map]->cell_has_players(proyectile_to_be_executed->pos_x, proyectile_to_be_executed->pos_y))
		{
			std::vector<Player*> my_vector_of_players = maps[actual_map]->get_cell_players(proyectile_to_be_executed->pos_x, proyectile_to_be_executed->pos_y);
			for (int i = 0; i < (int) my_vector_of_players.size(); i++)
			{
				
				action_to_be_loaded.my_info_header = Action_info_id::DIE;
				action_to_be_loaded.id = my_vector_of_players[i]->id;
				should_hit = true;
				notify_obs();
				should_hit = false;

			}
		}
	}
	else if (proyectile_to_be_executed->is_snowball())
	{
		if (maps[actual_map]->cell_has_enemies(proyectile_to_be_executed->pos_x, proyectile_to_be_executed->pos_y))
		{
			std::vector<Enemy*> my_vector_of_enemys = maps[actual_map]->get_cell_enemies(proyectile_to_be_executed->pos_x, proyectile_to_be_executed->pos_y);
			for (int i = 0; i < (int) my_vector_of_enemys.size(); i++)
			{

				action_to_be_loaded.my_info_header = Action_info_id::HIT;
				action_to_be_loaded.id = my_vector_of_enemys[i]->id;
				should_hit = true;
				notify_obs();
				should_hit = false;
			}
		}

	}

}


void Scene::execute_move(Action_info * move_to_be_executed, bool & should_die) {

	bool move_succesful;
	//bool enemy_can_be_moved;
	Player * the_one_that_moves = NULL;
	Position extern_destination;
	Direction_type my_direction;

	extern_destination.fil = move_to_be_executed->final_pos_x;
	extern_destination.col = move_to_be_executed->final_pos_y;
	my_direction = move_to_be_executed->my_direction;
	the_one_that_moves = get_player(move_to_be_executed->my_character);


	 if (maps[actual_map]->cell_has_enemies(extern_destination.fil, extern_destination.col))
	{
		std::vector<Enemy*> my_vector_of_enemys = maps[actual_map]->get_cell_enemies(extern_destination.fil, extern_destination.col);
		for (int i = 0; i < (int) my_vector_of_enemys.size(); i++)
		{
			if (((my_vector_of_enemys)[i]->current_state == States::Moving)&&((my_vector_of_enemys)[i]->current_state == States::Iddle))
			{					
				should_die = true;
				move_succesful = false;

					break;
			}
		}

		for (int i = 0; i < (int) my_vector_of_enemys.size(); i++)
		{
			if ((my_vector_of_enemys)[i]->amount_of_hits_taken>=3) //The enemy is snowballed
				if(my_direction==Direction_type::Right)
					maps[actual_map]->move_id((my_vector_of_enemys)[i]->id, extern_destination.fil, extern_destination.col+1); //The snowballed enemy moves along with the player
				else
					maps[actual_map]->move_id((my_vector_of_enemys)[i]->id, extern_destination.fil, extern_destination.col - 1); //The snowballed enemy moves along with the player


		}


	}
	 else if (maps[actual_map]->cell_has_enemy_proyectiles(extern_destination.fil, extern_destination.col))
	{
		should_die = true;
		move_succesful = false;
	}

	else
		move_succesful = true;


	if(move_succesful)
		maps[actual_map]->move_id(get_player(my_player)->id , extern_destination.fil, extern_destination.col); //

}

void Scene::execute_attack(Action_info * attack_to_be_executed) {

	Player * the_one_that_moves = NULL;
	Position extern_destination;
	//Position local_destination;
	Sense_type my_direction;

	extern_destination.fil = attack_to_be_executed->final_pos_x;
	extern_destination.col = attack_to_be_executed->final_pos_y;
	my_direction = (Sense_type)attack_to_be_executed->my_direction;
	the_one_that_moves = get_player(attack_to_be_executed->my_character);


	maps[actual_map]->place_on_map(extern_destination.fil, extern_destination.col, Item_type::SNOWBALL, my_direction, this);
}

void Scene::execute_enemy_action(Action_info * enemy_action_to_be_executed, bool & should_be_hit) {

		Position extern_destination;
		//Position local_destination;
		Enemy * the_enemy_that_acts = NULL;
		Sense_type my_direction;
		the_enemy_that_acts = (Enemy *)maps[actual_map]->get_from_map(enemy_action_to_be_executed->id);

		my_direction = (Sense_type)enemy_action_to_be_executed->my_direction;
		extern_destination.fil = enemy_action_to_be_executed->final_pos_x;
		extern_destination.col = enemy_action_to_be_executed->final_pos_y;

	if (enemy_action_to_be_executed->action == Action_type::Move)
	{
		if (maps[actual_map]->cell_has_players(extern_destination.fil, extern_destination.col))
		{
			std::vector<Player*> my_vector_of_players = maps[actual_map]->get_cell_players(extern_destination.fil, extern_destination.col);
			for (int i = 0; i < (int)my_vector_of_players.size(); i++)
			{
				action_to_be_loaded.my_info_header = Action_info_id::DIE;
				action_to_be_loaded.id = my_vector_of_players[i]->id;
				should_hit = true;
				notify_obs();
				should_hit = false;

			}
		}
		if (maps[actual_map]->cell_has_player_proyectiles(extern_destination.fil, extern_destination.col))
		{
			should_be_hit = true;
		}
		else
			maps[actual_map]->move_id(enemy_action_to_be_executed->id, extern_destination.fil, extern_destination.col); //
	}
	else if(enemy_action_to_be_executed->action == Action_type::Attack){
		maps[actual_map]->place_on_map(extern_destination.fil, extern_destination.col, Item_type::FIREBALL, my_direction, this);
	}
}


void Scene::load_new_map(bool is_client, const char * the_map, char the_checksum ) {

	al_flush_event_queue(enemy_actions_queue);
	al_flush_event_queue(proyectile_actions_queue);

	Map * new_map = new Map(12, 16, data);
	new_map->register_enemies_event_queue(enemy_actions_queue);
	new_map->register_proyectiles_event_queue(proyectile_actions_queue);
	new_map->append_graphic_facility(graphics);
	
	if (is_client) //The map came by networking
	{	
		new_map->load_on_map(the_map);
		new_map->load_checksum(the_checksum);
		
		this->actual_map++;		
	}
	else
	{	//I´m server, I´ve the map available

		new_map->load_on_map(give_me_the_CSV(actual_map));
		new_map->load_checksum(this->make_checksum(give_me_the_CSV(actual_map)));
	}
	#pragma message(//THIS NEXT FUNCTION DEPENDS ON HAVING THE actual_map VALUE SET ON THE LAST CREATED MAP INDEX!!)
	//THIS NEXT FUNCTION DEPENDS ON HAVING THE actual_map VALUE SET ON THE LAST CREATED MAP INDEX!!
	load_new_graphic_level();
	curr_enemies = new_map->get_all_enemies();
	for (std::vector<Enemy*>::iterator it = curr_enemies->begin(); it != curr_enemies->end(); ++it)
		this->add_observer(new EnemySceneObserver(*it, this));

	curr_players = new_map->get_all_players();
	for (std::vector<Player*>::iterator it = curr_players->begin(); it != curr_players->end(); ++it)
		this->add_observer(new PlayerSceneObserver(*it, this));

	curr_proyectiles = new_map->get_all_proyectiles();

	maps.push_back(new_map);

}

//hace checksum , función guido
unsigned char Scene::make_checksum(const char * CSV_map_location) {

	unsigned char local_checksum = 0; 
	const unsigned char* table = getTable();

	for (int i = 0; i < FILE_LENGHT; i++)
	{
		local_checksum = table[local_checksum^CSV_map_location[i]];
//		cout << (unsigned int)index << ' ';
	}

	return local_checksum;
}//después usar esta función que haga guido para el checksum de mapas que llegan para validarlos(hecho)


bool Scene::is_the_map_okay(const char * the_map , char the_checksum )
{
	bool map_validation;
	unsigned char extern_checksum = the_checksum;
	unsigned char local_checksum = this->make_checksum(the_map);

	if (local_checksum == extern_checksum)
		map_validation = true;
	else
		map_validation = false;
	
	return map_validation;
}

void Scene::load_new_graphic_level()
{
	load_graphic_level = true;
	notify_obs();
	load_graphic_level = false;
}

//función que hacce guido, va al archivo, lo convierte a const char* y lo devuelve
const char * Scene::give_me_the_CSV(unsigned int actual_map) {

	ifstream myFile;
	string mapFile = "levels/level " + to_string(actual_map+1) + ".csv";
	myFile.open(mapFile.c_str());
	char *map = new char[192];
	int i = 0;
	bool comaDelim = false;					// asumimos que el csv esta separado por ';'

	while (myFile.good() && !comaDelim)
	{
		string line;
		getline(myFile, line, ';');
		if (line.length() > 5)
			comaDelim = true;			// si la linea es muy larga el csv esta separado por ','
		else
		{
			map[i] = line.c_str()[0];
			i++;
		}
		for (int j = 1; j < 15; j++)
		{
			string line;
			getline(myFile, line, ';');
			map[i] = line.c_str()[0];
			i++;
		}
		getline(myFile, line, '\n');
		map[i] = line.c_str()[0];
		i++;
	}

	myFile.close();

	if (comaDelim)														// el delimitador so, ',' no ';'
	{
		myFile.open(mapFile.c_str());
		int i = 0;
		while (myFile.good())
		{
			for (int j = 0; j < 15; j++)
			{
				string line;
				getline(myFile, line, ',');
				map[i] = line.c_str()[0];
				i++;
			}
			string line;
			getline(myFile, line, '\n');
			map[i] = line.c_str()[0];
			i++;
		}

		myFile.close();
	}
	
	return map;
}

const char * Scene::give_me_the_map_info()
{
	return maps[actual_map]->give_me_the_original_map();
}

Action_info Scene::give_me_my_enemy_action(bool is_initializing){
	
	if(is_initializing){
		enemy_action_info = maps[actual_map]->get_initial_enemy_actions();

		if (enemy_action_info.finished_loading) //ENEMYS_LOADED VA DEVOLVER UN BOOALEANO, CHEQUEAR ESO!!!!!!!!
		{
			enemys_ready = true;
			notify_obs();
			enemys_ready = false;
		}
	}
	//si no esta inicializado directamente ya esta cargado cuando llega su turno de ser pedido, 
	//unicamente lo van a llamar los observer con is_initializing= false
	return enemy_action_info;

}


void Scene::gameInit() {	

	this->game_started = true;	//indica que todo inicializo correctamente y entonces debe empezar a funcionar la FSM.
	notify_obs();
	this->game_started = false;

}


Item_type Scene::give_me_my_player() {

	return this-> my_player;
}

Item_type Scene::give_the_other_player() {

	return this->other_player;
}


bool Scene::both_players_dead()
{
	for(std::vector<Player*>::iterator it = curr_players->begin(); it != curr_players->end(); ++it)
		if (!(*it)->is_dead()) 
			return false;

	return true;
}

bool Scene::any_monsters_left()
{

	for (std::vector<Enemy*>::iterator it = curr_enemies->begin(); it != curr_enemies->end(); ++it)
		if (!(*it)->is_dead())
			return true;

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
bool Scene::is_the_action_possible( Action_info * package_to_be_analyze) {

	bool is_the_action_possible = false;


	switch (package_to_be_analyze->my_info_header)
	{
	case Action_info_id::MOVE:

		is_the_action_possible=check_move(package_to_be_analyze);
		break;

	case Action_info_id::ATTACK:

		is_the_action_possible = check_attack(package_to_be_analyze);
		break;

	case Action_info_id::ACTION_REQUEST:

		if(package_to_be_analyze->action == Action_type::Move)
			is_the_action_possible = check_move(package_to_be_analyze);
		else
			is_the_action_possible = check_attack(package_to_be_analyze);

		break;

	case Action_info_id::ENEMY_ACTION:
		is_the_action_possible = check_enemy_action(package_to_be_analyze);
		break;

	default:
		std::cout << "Acción no analizable" << std::endl;
		break;

	}


	return is_the_action_possible;
}

bool Scene::check_move(Action_info * Action_info_to_be_checked ) {

	bool is_the_move_possible;
	Player * the_one_that_moves = NULL;
	Position extern_destination;
	Position local_destination;
	Direction_type my_direction;

	//hacer funcion ´para evitar chocclo que reciba parámetros, si es local, ptr my_direction para modificarlo ahí adentro y el destino
	if (Action_info_to_be_checked->is_local)
	{
		Action_info_to_be_checked->my_character = my_player;
		the_one_that_moves = get_player(my_player);
		action_to_be_loaded_id = the_one_that_moves->id;
		my_direction = Action_info_to_be_checked->my_direction;

	}
	else
	{
		Action_info_to_be_checked->my_character = other_player;
		the_one_that_moves = get_player(other_player);
		action_to_be_loaded_id = the_one_that_moves->id;

		extern_destination.fil = Action_info_to_be_checked->final_pos_x;
		extern_destination.col = Action_info_to_be_checked->final_pos_y;

		Action_info_to_be_checked->my_direction = load_direction(&extern_destination, the_one_that_moves);

	}



	if (the_one_that_moves->is_dead())
	{
		is_the_move_possible = false;
		std::cout << " Error , el jugador que debería moverse está muerto" << std::endl;

	}
	else
	{

		int delta = 0;
		switch (my_direction)
		{

		case Direction_type::Left:
			delta = -1;
			is_the_move_possible = Action_info_to_be_checked->is_local ? maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x, the_one_that_moves->pos_y + delta) : maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col);
			if (Action_info_to_be_checked->is_local)
			{
				local_destination.fil = the_one_that_moves->pos_x;
				local_destination.col = the_one_that_moves->pos_y + delta;
			}
			break;

		case Direction_type::Right:
			delta = 1;
			is_the_move_possible = Action_info_to_be_checked->is_local ? maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x, the_one_that_moves->pos_y + delta) : maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col);
			if (Action_info_to_be_checked->is_local)
			{
				local_destination.fil = the_one_that_moves->pos_x;
				local_destination.col = the_one_that_moves->pos_y + delta;
			}
			break;

		case Direction_type::Jump_Straight:
			delta = -1;
			if (Action_info_to_be_checked->is_local)
			{
				local_destination.fil = the_one_that_moves->pos_x + delta;
				local_destination.col = the_one_that_moves->pos_y;
			}
			break;

		case Direction_type::Jump_Left:
			if (Action_info_to_be_checked->is_local)
			{
				local_destination.fil = the_one_that_moves->pos_x - 2;
				local_destination.col = the_one_that_moves->pos_y-1;
			}
			break;
		case Direction_type::Jump_Right:			
			if (Action_info_to_be_checked->is_local)
			{
				local_destination.fil = the_one_that_moves->pos_x - 2;
				local_destination.col = the_one_that_moves->pos_y + 1;
			}
											
			is_the_move_possible = true;
			break;


		default:
			std::cout << " Error , no se recibió un MOVE para analizar" << std::endl;
			break;
		}
	}

	if (is_the_move_possible && Action_info_to_be_checked->is_local) //load the destination column and row in the eventpackage
	{
		Action_info_to_be_checked->final_pos_x=local_destination.fil;
		Action_info_to_be_checked->final_pos_y = local_destination.col;
	}

	return is_the_move_possible;
}

Direction_type Scene::load_direction(Position * extern_destination, Character* the_one_that_moves) {

	Direction_type my_direction;

	if ((extern_destination->fil == the_one_that_moves->pos_x) && (extern_destination->col < the_one_that_moves->pos_y)) //Left
		my_direction = Direction_type::Left;
	else if ((extern_destination->fil == the_one_that_moves->pos_x) && (extern_destination->col > the_one_that_moves->pos_y)) //Right
		my_direction = Direction_type::Right;
	else if ((extern_destination->fil < the_one_that_moves->pos_x) && (extern_destination->col == the_one_that_moves->pos_y)) //Jump_Straight
		my_direction = Direction_type::Jump_Straight;
	else if ((extern_destination->fil < the_one_that_moves->pos_x) && (extern_destination->col < the_one_that_moves->pos_y)) //Jump_Left
		my_direction = Direction_type::Jump_Left;
	else if ((extern_destination->fil < the_one_that_moves->pos_x) && (extern_destination->col > the_one_that_moves->pos_y)) //Jump_Right
		my_direction = Direction_type::Jump_Right;

	return my_direction;
}




bool Scene::check_attack(Action_info * Action_info_to_be_checked) {

	bool is_the_attack_possible;
	Player * the_one_that_attacks = NULL;
	Position extern_destination;
	Position local_destination;
	Sense_type in_witch_direction_is_he_looking;



	if (Action_info_to_be_checked->is_local)
	{
		Action_info_to_be_checked->my_character = my_player;
		the_one_that_attacks = get_player(my_player);
		action_to_be_loaded_id = the_one_that_attacks->id;
		in_witch_direction_is_he_looking = the_one_that_attacks->get_sense();
	}
	else
	{
		Action_info_to_be_checked->my_character = other_player;
		the_one_that_attacks = get_player(other_player);
		action_to_be_loaded_id = the_one_that_attacks->id;

		extern_destination.fil = Action_info_to_be_checked->final_pos_x;
		extern_destination.col = Action_info_to_be_checked->final_pos_y;

		if ((extern_destination.fil == the_one_that_attacks->pos_x) && (extern_destination.col < the_one_that_attacks->pos_y)) //Left
		{
			in_witch_direction_is_he_looking = Sense_type::Left;
			Action_info_to_be_checked->my_direction = Direction_type::Left;
		}
		else  //Right
		{
			in_witch_direction_is_he_looking = Sense_type::Right;
			Action_info_to_be_checked->my_direction = Direction_type::Right;
		}

	}


	if (the_one_that_attacks->is_dead())
	{
		is_the_attack_possible = false;
		std::cout << " Error , el jugador que debería atacar está muerto" << std::endl;
	}
	else
	{
		int delta = 0;

		if (in_witch_direction_is_he_looking == Sense_type::Left)
		{
			delta = -1;
			is_the_attack_possible = Action_info_to_be_checked->is_local ? maps[actual_map]->cell_has_floor(the_one_that_attacks->pos_x, the_one_that_attacks->pos_y + delta) : maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col);
			if (Action_info_to_be_checked->is_local)
			{
				local_destination.fil = the_one_that_attacks->pos_x;
				local_destination.col = the_one_that_attacks->pos_y + delta;
			}

		
		}
		else //Sense_type::Right
		{
			delta = 1;
			is_the_attack_possible = Action_info_to_be_checked->is_local ? maps[actual_map]->cell_has_floor(the_one_that_attacks->pos_x, the_one_that_attacks->pos_y + delta) : maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col);
			if (Action_info_to_be_checked->is_local)
			{
				local_destination.fil = the_one_that_attacks->pos_x;
				local_destination.col = the_one_that_attacks->pos_y + delta;
			}

		}

	}

	if (is_the_attack_possible && Action_info_to_be_checked->is_local) //load the destination column and row in the eventpackage
	{
		Action_info_to_be_checked->final_pos_x = local_destination.fil;
		Action_info_to_be_checked->final_pos_y = local_destination.col;

		if (in_witch_direction_is_he_looking == Sense_type::Left)
			Action_info_to_be_checked->my_direction = Direction_type::Left;
		else
			Action_info_to_be_checked->my_direction = Direction_type::Right;

	}

	return is_the_attack_possible;
}


bool Scene::check_enemy_action(Action_info * package_to_be_analyze) {

	bool is_the_enemy_action_possible = false;
	Enemy * the_enemy_that_acts = NULL;
	Sense_type in_witch_direction_is_he_looking;
	Position extern_destination;
	Action_type action_to_be_checked;
	Direction_type my_direction;
	


		the_enemy_that_acts =(Enemy *) maps[actual_map]->get_from_map(package_to_be_analyze->id);
		action_to_be_loaded_id = the_enemy_that_acts->id;

		extern_destination.fil = package_to_be_analyze->final_pos_x;
		extern_destination.col = package_to_be_analyze->final_pos_y;
		action_to_be_checked = package_to_be_analyze->action;


		if (the_enemy_that_acts->is_dead())
		{
			std::cout << " Error , el mounstro que debería actuar está muerto" << std::endl;
			is_the_enemy_action_possible = false;
		}
		else
		{
			switch (action_to_be_checked)
			{
			case Action_type::Move:

				my_direction = load_direction(&extern_destination, the_enemy_that_acts);

				switch (my_direction)
				{
				case Direction_type::Left:

						if (maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col - 1))
							is_the_enemy_action_possible = false;
						else
							is_the_enemy_action_possible = true;

					break;

				case Direction_type::Right:

						if (maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col + 1))
							is_the_enemy_action_possible = false;
						else
							is_the_enemy_action_possible = true;				
					break;

				case Direction_type::Jump_Straight: 

				case Direction_type::Jump_Left:

				case Direction_type::Jump_Right:
					
					break;

				default:
					std::cout << " Error , no se recibió un MOVE para analizar" << std::endl;
					break;
				}

				break;

			case Action_type::Attack:

				if ((extern_destination.fil == the_enemy_that_acts->pos_x) && (extern_destination.col < the_enemy_that_acts->pos_y))
					in_witch_direction_is_he_looking = Sense_type::Left;
				else
					in_witch_direction_is_he_looking = Sense_type::Right;


				if (in_witch_direction_is_he_looking == Sense_type::Left) //Left
				{
					if (maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col - 1))
						is_the_enemy_action_possible = false;
					else
						is_the_enemy_action_possible = true;
				}
				else  //Right
				{
					in_witch_direction_is_he_looking = Sense_type::Right;
					if (maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col + 1))
						is_the_enemy_action_possible = false;
					else
						is_the_enemy_action_possible = true;
				}

				break;

			default:
				std::cout << "Error, Un EA con acción desconocida" << std::endl;
				break;
			}
		
	}

	return is_the_enemy_action_possible;
}

bool Scene::check_if_has_to_fall(unsigned int id) {

	MapThing * element_to_be_checked= maps[actual_map]->get_from_map(id);

	return (maps[actual_map]->cell_has_floor(element_to_be_checked->pos_x + 1, element_to_be_checked->pos_y));
}

bool Scene::check_position(Action_info position_info) {

	return maps[actual_map]->cell_has_floor(position_info.final_pos_x, position_info.final_pos_y);
}


Player * Scene::get_player(Item_type player_to_be_found) {

	Player * player_found = NULL;
	//usar get_from_map()
	//std::vector<Player*>* my_vector_of_players= maps[actual_map]->get_all_players();
	if ((*curr_players)[0]->get_printable() == player_to_be_found)
		player_found = (*curr_players)[0];
	else
		player_found = (*curr_players)[1];

	return player_found;
}

bool Scene::did_we_win()
{
	bool we_won;

	if ((!this->both_players_dead()) && (!this->any_monsters_left()) && (this->actual_map == 10))
	{
		we_won = true;

	}
	else
		we_won = false;

	return we_won;
}

bool Scene::did_we_lose()
{
	bool we_lost;

	if (this->both_players_dead())
	{
		we_lost = true;
	}
	else
		we_lost = false;

	return we_lost;
}

//For server´s 
void Scene::check_current_game_situation() {

	if (both_players_dead()){
		we_lost = true;
		notify_obs();
		we_lost = false;
	}
	else if ((!any_monsters_left()) && (actual_map == 10)){
		we_won = true;
		notify_obs();
		we_won = false;
	}

}

void Scene::append_new_auxilar_event(Action_info new_action_info) {
	assistant_queue->push(new_action_info);
}

//esta funcion solo tiene que ser llamada por el server!!!!
void Scene::control_enemy_actions()
{
	ALLEGRO_EVENT * allegroEvent = NULL;
	while (al_get_next_event(enemy_actions_queue, allegroEvent)) 
		if (allegroEvent->type == ALLEGRO_EVENT_TIMER) {
			Enemy* wanted_enemy = get_enemy_to_act_on(allegroEvent->timer.source);
			if (wanted_enemy != NULL) {
				enemy_action_info = wanted_enemy->act();
				new_enemy_action = true;
				notify_obs();
				new_enemy_action = false;
			}
		}
}

void Scene::control_proyectile_actions() {
	ALLEGRO_EVENT * allegroEvent = NULL;
	while (al_get_next_event(proyectile_actions_queue, allegroEvent))
		if (allegroEvent->type == ALLEGRO_EVENT_TIMER) {
			Proyectile* wanted_proyectile = get_proyectile_to_act_on(allegroEvent->timer.source);
			//if (wanted_proyectile != NULL)
				//wanted_proyectile->act();			//aca en realidad deberia agregar un paquete!!
		}
}

Enemy * Scene::get_enemy_to_act_on(ALLEGRO_TIMER *timer)
{
	for (std::vector<Enemy*>::iterator it = curr_enemies->begin(); it != curr_enemies->end(); ++it)
		if ((*it)->get_acting_timer() == timer)
			return (*it);

	return NULL;
}

Proyectile * Scene::get_proyectile_to_act_on(ALLEGRO_TIMER *timer) {
	for (std::vector<Proyectile*>::iterator it = curr_proyectiles->begin(); it != curr_proyectiles->end(); ++it)
		if ((*it)->get_moving_timer() == timer)
			return (*it);

	return NULL;
}

Position Scene::shortest_movement_2_nearest_player(PurpleGuy* purple_guy) {
	Player* nearest_player = find_nearest_player(purple_guy->pos_x, purple_guy->pos_y);
	Position next_movement;
	next_movement = maps[actual_map]->find_next_movement_4_shortest_path(purple_guy->pos_x, purple_guy->pos_y, nearest_player->pos_x, nearest_player->pos_y);
	return next_movement;
}

void Scene::append_graphic_facility(void * drawer)
{
	this->graphics = drawer;
}


Player* Scene::find_nearest_player(int pos_x, int pos_y) {
	int shortest_distance = INT_MAX;
	Player* nearest_player = NULL;

	for(std::vector<Player*>::iterator it = curr_players->begin(); it != curr_players->end(); ++it){

		Player* curr_player = (*it);
		int taxi_distance = abs(curr_player->pos_x - pos_x) + abs(curr_player->pos_y - pos_y);		//function abs returns an int type

		if(shortest_distance > taxi_distance){
			shortest_distance =  taxi_distance;
			nearest_player = curr_player;
		}
	}
	return nearest_player;
}


const unsigned char *getTable()
{
	std::ifstream myFile;
	myFile.open(TABLE_FILE);
	unsigned char *table = new unsigned char;
	int i = 0;

	while (myFile.good())
	{
		std::string line;
		std::getline(myFile, line, ',');
		table[i] = atoi(line.c_str());
//		cout << (int)table[i] << ' ';
		i++;
	}

	myFile.close();

	return table;
}

void Scene::load_action_on_character(Action_info action) {

	action_to_be_loaded = action;
	load_action_on_char = true;
	notify_obs();
	load_action_on_char = false;
}

unsigned int Scene::get_action_to_be_loaded_id() {
	return action_to_be_loaded_id;
}

Action_info Scene::get_action_to_be_loaded()
{
	return action_to_be_loaded;
}
