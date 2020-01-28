#include "Scene.h"
#include "general.h"
#include <fstream>
#include <string>
#include "EnemySceneObserver.h"
#include "PlayerSceneObserver.h"
#include <algorithm>    // std::find_if

#define AMOUNT_COLS	16
#define AMOUNT_FILS	12
#define FILE_LENGHT (AMOUNT_COLS*AMOUNT_FILS)

using namespace std;

static int searched_id;
static bool proy_meets_id(Proyectile* proy);
static bool char_meets_id(Character* charac);

static const unsigned char checksum_table[256] = { 98, 6, 85, 150, 36, 23, 112, 164, 135, 207, 169, 5, 26, 64, 165, 219,
													61, 20, 68, 89, 130, 63, 52, 102, 24, 229, 132, 245, 80, 216, 195, 115,
													90, 168, 156, 203, 177, 120, 2, 190, 188, 7, 100, 185, 174, 243, 162, 10,
													237, 18, 253, 225, 8, 208, 172, 244, 255, 126, 101, 79, 145, 235, 228, 121,
													123, 251, 67, 250, 161, 0, 107, 97, 241, 111, 181, 82, 249, 33, 69, 55,
													59, 153, 29, 9, 213, 167, 84, 93, 30, 46, 94, 75, 151, 114, 73, 222,
													197, 96, 210, 45, 16, 227, 248, 202, 51, 152, 252, 125, 81, 206, 215, 186,
													39, 158, 178, 187, 131, 136, 1, 49, 50, 17, 141, 91, 47, 129, 60, 99,
													154, 35, 86, 171, 105, 34, 38, 200, 147, 58, 77, 118, 173, 246, 76, 254,
													133, 232, 196, 144, 198, 124, 53, 4, 108, 74, 223, 234, 134, 230, 157, 139,
													189, 205, 199, 128, 176, 19, 211, 236, 127, 192, 231, 70, 233, 88, 146, 44,
													183, 201, 22, 83, 13, 214, 116, 109, 159, 32, 95, 226, 140, 220, 57, 12,
													221, 31, 209, 182, 143, 92, 149, 184, 148, 62, 113, 65, 37, 27, 106, 166,
													3, 14, 204, 72, 21, 41, 56, 66, 28, 193, 40, 217, 25, 54, 179, 117,
													238, 87, 240, 155, 180, 170, 242, 212, 191, 163, 78, 218, 137, 194, 175, 110,
													43, 119, 224, 71, 122, 142, 42, 160, 104, 48, 247, 103, 15, 11, 138, 239 };

static bool proy_meets_id(Proyectile* proy) {
	return proy->id == searched_id;
}
static bool char_meets_id(Character* charac) {
	return charac->id == searched_id;
}

Scene::Scene(Userdata* data, Item_type my_player, Item_type his_player):Observable()
{
	this->assistant_queue = new queue<Action_info>();
	this->saved_events = new queue<EventPackage *>();

	//this->action_from_allegro = NULL;
	this->actual_map = -1;
	enemy_action_info;
	this->data = data;
	this->other_player = his_player;
	this->my_player = my_player;
}


Scene::~Scene()
{
	delete assistant_queue;
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
	case Action_info_id::PROY_MOVE:
		execute_proy_move(action_to_be_executed, should_be_hit);
		break;
	default:
		cout << "Error, Acción no ejecutable" << endl;
		break;

	}

}

void Scene::execute_proyectile(Proyectile* proyectile_to_be_executed, bool& should_be_hit) {

	Proyectile * my_projectile = (Proyectile *)maps[actual_map]->get_from_map(proyectile_to_be_executed->id);

	if (proyectile_to_be_executed->is_fireball())
	{
		if (maps[actual_map]->cell_has_players(proyectile_to_be_executed->pos_x, proyectile_to_be_executed->pos_y))
		{
			vector<Player*> my_vector_of_players = maps[actual_map]->get_cell_players(proyectile_to_be_executed->pos_x, proyectile_to_be_executed->pos_y);
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
			vector<Enemy*> my_vector_of_enemys = maps[actual_map]->get_cell_enemies(proyectile_to_be_executed->pos_x, proyectile_to_be_executed->pos_y);
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

	bool move_succesful = true;
	//bool enemy_can_be_moved;
	Player * the_one_that_moves = NULL;
	Position extern_destination;
	Direction_type my_direction;

	extern_destination.fil = move_to_be_executed->final_pos_x;		//CAMBIO ACA
	extern_destination.col = move_to_be_executed->final_pos_y;
	my_direction = move_to_be_executed->my_direction;
	the_one_that_moves = get_player(move_to_be_executed->my_character);


	if (maps[actual_map]->cell_has_enemies(extern_destination.fil, extern_destination.col))
	{
		vector<Enemy*> my_vector_of_enemys = maps[actual_map]->get_cell_enemies(extern_destination.fil, extern_destination.col);
		for (int i = 0; i < (int) my_vector_of_enemys.size(); i++)
		{
			Enemy* curr_enemy = (my_vector_of_enemys)[i];
			if (curr_enemy->is_moving() || curr_enemy->is_iddle())
			{
				should_die = true;
				move_succesful = false;
				break;
			}
		}

		if(move_succesful)
			for (int i = 0; (i < (int) my_vector_of_enemys.size()) && move_succesful; i++)
			{
				if ((my_vector_of_enemys)[i]->amount_of_hits_taken >= 3)			//The enemy is snowballed
					if (my_direction == Direction_type::Right || my_direction == Direction_type::Jump_Right)
						maps[actual_map]->move_id((my_vector_of_enemys)[i]->id, extern_destination.fil, extern_destination.col + 1); //The snowballed enemy moves along with the player
					else
						maps[actual_map]->move_id((my_vector_of_enemys)[i]->id, extern_destination.fil, extern_destination.col - 1); //The snowballed enemy moves along with the player

			}
	}
	else if (maps[actual_map]->cell_has_enemy_proyectiles(extern_destination.fil, extern_destination.col))
	{
		should_die = true;
		move_succesful = false;
	}

	if(move_succesful)
		maps[actual_map]->move_id(the_one_that_moves->id , extern_destination.fil, extern_destination.col); //

}

void Scene::execute_attack(Action_info * attack_to_be_executed) {

	Player * the_one_that_moves = NULL;
	Position extern_destination;
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
			vector<Player*> my_vector_of_players = maps[actual_map]->get_cell_players(extern_destination.fil, extern_destination.col);
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

void Scene::execute_proy_move(Action_info * action_to_be_executed, bool & should_be_hit)
{
	Map* curr_map = maps[actual_map];
	searched_id = action_to_be_executed->id;
	Proyectile* proy = *find_if(curr_proyectiles->begin(), curr_proyectiles->end(), proy_meets_id);

	curr_map->move_map_thing(proy, action_to_be_executed->final_pos_x, action_to_be_executed->final_pos_y);

	if (proy->is_fireball()) {
		if (should_be_hit = curr_map->cell_has_players(action_to_be_executed->final_pos_x, action_to_be_executed->final_pos_y)) {
			vector<Player*> players = curr_map->get_cell_players(action_to_be_executed->final_pos_x, action_to_be_executed->final_pos_y);
			for (vector<Player*>::iterator player = players.begin(); player != players.end(); ++player)
				(*player)->ev_handler->get_ev_gen()->append_new_event(new DIED_EventPackage(), 0);
		}
	}
	else if (proy->is_snowball())
		if (should_be_hit = curr_map->cell_has_enemies(action_to_be_executed->final_pos_x, action_to_be_executed->final_pos_y)) {
			vector<Enemy*> enemies = curr_map->get_cell_enemies(action_to_be_executed->final_pos_x, action_to_be_executed->final_pos_y);
			for (vector<Enemy*>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
				(*enemy)->ev_handler->get_ev_gen()->append_new_event(new GOT_HIT_EventPackage(), 0);
		}
}

void Scene::load_new_map(bool is_client, const unsigned char * the_map, char the_checksum ) {

	Map * new_map = new Map(12, 16, data);
	new_map->append_graphic_facility(graphics);

	if (is_client) //The map came by networking
	{
		//if (actual_map == -1)
		//	actual_map++;
		new_map->load_on_map(the_map, this);
		new_map->load_checksum(the_checksum);
		this->actual_map++;
	}
	else
	{	//I´m server, I´ve the map available
		this->actual_map++;
		//string map_string = give_me_the_CSV(actual_map);
		//new_map->load_on_map(map_string.c_str(),this);
		//new_map->load_checksum(make_checksum(map_string.c_str()));
		new_map->load_on_map(the_map,this);
		new_map->load_checksum(make_checksum(the_map));
	}

	curr_enemies = new_map->get_all_enemies();
	for (vector<Enemy*>::iterator it = curr_enemies->begin(); it != curr_enemies->end(); ++it)
		add_observer(new EnemySceneObserver(*it, this));

	curr_players = new_map->get_all_players();
	for (vector<Player*>::iterator it = curr_players->begin(); it != curr_players->end(); ++it)
		add_observer(new PlayerSceneObserver(*it, this));

	curr_proyectiles = new_map->get_all_proyectiles();

	maps.push_back(new_map);
	//THIS NEXT FUNCTION DEPENDS ON HAVING THE actual_map VALUE SET ON THE LAST CREATED MAP INDEX!!
	load_new_graphic_level();

}

unsigned char Scene::make_checksum(const unsigned char * CSV_map_location) {

	unsigned char local_checksum = 0;

	for (int i = 0; i < FILE_LENGHT; i++)
		local_checksum = checksum_table[local_checksum^CSV_map_location[i]];

	return local_checksum;
}

bool Scene::is_the_map_okay(const unsigned char * the_map , char the_checksum )
{
	return make_checksum(the_map) == the_checksum;
}

void Scene::load_new_graphic_level()
{
	load_graphic_level = true;
	notify_obs();					//ScenarioDRAWObserver
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
		if (line.length() > 5) {
			comaDelim = true;			// si la linea es muy larga el csv esta separado por ','
			myFile.close();
			break;
		}
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
	}
	myFile.close();

	return map;
}

const unsigned char * Scene::give_me_the_map_info()
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

	game_started = true;	//indica que todo inicializo correctamente y entonces debe empezar a funcionar la FSM.
	notify_obs();
	game_started = false;

}

Item_type Scene::give_me_my_player() {

	return my_player;
}

Item_type Scene::give_the_other_player() {

	return other_player;
}

bool Scene::both_players_dead()
{
	for(vector<Player*>::iterator it = curr_players->begin(); it != curr_players->end(); ++it)
		if (!(*it)->is_dead())
			return false;

	return true;
}

bool Scene::any_monsters_left()
{

	for (vector<Enemy*>::iterator it = curr_enemies->begin(); it != curr_enemies->end(); ++it)
		if (!(*it)->is_dead())
			return true;

	return false;
}

bool Scene::game_is_finished() {
	return game_finished;
}

void Scene::finish_game() {
	game_finished = true;
	notify_obs();
	game_finished = false;
}


//analizo jugadas externas e internas relacionadas a scene
bool Scene::is_the_action_possible(Action_info * package_to_be_analyze, bool map_thing_check) {

	bool is_the_action_possible = false;


	switch (package_to_be_analyze->my_info_header)
	{
	case Action_info_id::MOVE:
		is_the_action_possible = check_move(package_to_be_analyze, map_thing_check);
		break;

	case Action_info_id::ATTACK:
		is_the_action_possible = check_attack(package_to_be_analyze, map_thing_check);
		break;

	case Action_info_id::ACTION_REQUEST:

		if(package_to_be_analyze->action == Action_type::Move)
			is_the_action_possible = check_move(package_to_be_analyze, map_thing_check);
		else
			is_the_action_possible = check_attack(package_to_be_analyze, map_thing_check);

		break;

	case Action_info_id::ENEMY_ACTION:
		is_the_action_possible = check_enemy_action(package_to_be_analyze);
		break;
	case Action_info_id::PROY_MOVE:
		is_the_action_possible = check_proy_move(package_to_be_analyze);
		break;
	default:
		cout << "Acción no analizable" << endl;
		break;

	}



	return is_the_action_possible;
}

bool Scene::check_proy_move(Action_info * Action_info_to_be_checked) {
	return maps[actual_map]->cell_has_floor(Action_info_to_be_checked->final_pos_x, Action_info_to_be_checked->final_pos_y);
}

bool Scene::check_move(Action_info * Action_info_to_be_checked, bool character_check) {
	cout << endl << "Entro CHECK" << endl;
	bool is_the_move_possible;
	Position local_destination;
	local_future_event = false;

	/*	if this particular scene is a client scene and the move comes from networking, then the character is
		already specified in Action_info_to_be_checked.*/
	if(!character_check)
		if (Action_info_to_be_checked->is_local || !data->my_network_data.is_client())
			Action_info_to_be_checked->my_character = Action_info_to_be_checked->is_local ? my_player : other_player;

	Player * the_one_that_moves = get_player(Action_info_to_be_checked->my_character);

	if (!Action_info_to_be_checked->is_local){
		bool out_of_range = false;
		Position extern_destination = { Action_info_to_be_checked->final_pos_y, Action_info_to_be_checked->final_pos_x };
		Action_info_to_be_checked->my_direction = load_direction(&extern_destination, the_one_that_moves, &out_of_range);
	}

	Action_info_to_be_checked->id = the_one_that_moves->id;
	Direction_type my_direction = Action_info_to_be_checked->my_direction;
	

	if (!character_check && !the_one_that_moves->is_iddle())
	{

//		if (saved_events->empty())
//		{
//			this->appended_event = true;
//#ifdef DEBUG
//			std::cout << "No se puede ejecutar el movimiento, el jugador ya se esta moviendo, se guarda el evento para más tarde" << std::endl;
//#endif
//		}
//		else
//			std::cout << "Ya hay guardado un movimiento" << std::endl;

			this->local_future_event = true;
#ifdef DEBUG
			std::cout << "Llego un evento mientras se está moviendo el personaje" << std::endl;
#endif


	}

	if (the_one_that_moves->is_dead())
	{
		is_the_move_possible = false;
#ifdef DEBUG
		std::cout << " Error , el jugador que debería moverse está muerto" << std::endl;
#endif
	}
	else
	{
		int delta = 0;
		switch (my_direction)
		{
		case Direction_type::Jump_Straight:
			if (Action_info_to_be_checked->is_local) {
				local_destination.fil = the_one_that_moves->pos_x;
				local_destination.col = the_one_that_moves->pos_y - 1;
			}
			
			if (character_check)
			{
				is_the_move_possible = maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x, the_one_that_moves->pos_y - 1);
				std::cout << "Chequeo de jump desde character" << std::endl;
				std::cout << "Altura del player: " << the_one_that_moves->pos_y << std::endl;
			}
			else
			{
				if(!(is_the_move_possible = maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x, the_one_that_moves->pos_y - 2)))
					is_the_move_possible = maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x, the_one_that_moves->pos_y - 1);
				std::cout << "Chequeo de jump desde fsm" << std::endl;
				std::cout << "Altura del player: "<< the_one_that_moves->pos_y << std::endl;
			}
			break;

		case Direction_type::Jump_Left:
		case Direction_type::Jump_Right:

			delta = (my_direction == Direction_type::Jump_Left) ? -1 : 1;

			if (Action_info_to_be_checked->is_local) {
				local_destination.fil = the_one_that_moves->pos_x + delta;
				local_destination.col = the_one_that_moves->pos_y - 2;
			}
			if (!character_check)	delta = 0;
			is_the_move_possible = maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x + delta, the_one_that_moves->pos_y - 1);

			break;

		case Direction_type::Left:
		case Direction_type::Right:
			if(this->appended_event||this->local_future_event)
				delta = (my_direction == Direction_type::Left) ? -2 : 2;
			else
				delta = (my_direction == Direction_type::Left) ? -1 : 1;

			is_the_move_possible = Action_info_to_be_checked->is_local ?
				maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x + delta, the_one_that_moves->pos_y) :
				maps[actual_map]->cell_has_floor(Action_info_to_be_checked->final_pos_x, Action_info_to_be_checked->final_pos_y);
			if (Action_info_to_be_checked->is_local)
			{
				local_destination.fil = the_one_that_moves->pos_x + delta;
				local_destination.col = the_one_that_moves->pos_y;
			}

			break;
		default:
			is_the_move_possible = false;
			std::cout << " Error , no se recibió un MOVE para analizar" << std::endl;
			break;
		}
	}
	if (is_the_move_possible && Action_info_to_be_checked->is_local) //load the destination column and row in the eventpackage to be send by networking
	{
		Action_info_to_be_checked->final_pos_x = local_destination.fil;
		Action_info_to_be_checked->final_pos_y = local_destination.col;
	}

	//if (logic_movements_block)
	//{
	//	is_the_move_possible = false;
	//	cout << "Movimiento no valido, bloqueo logico en proceso" << endl;
	//}
	//else if (is_the_move_possible)
	//{
	//	logic_movements_block = true;
	//	cout << "Movimiento valido, se activa bloqueo logico" << endl;
	//}

	return is_the_move_possible;
}

Direction_type Scene::load_direction(Position * extern_destination, Character* the_one_that_moves, bool* out_of_range) {

	Direction_type my_direction;

	if ((extern_destination->fil == the_one_that_moves->pos_y) && (extern_destination->col < the_one_that_moves->pos_x)) { //Left
		my_direction = Direction_type::Left;
		*out_of_range = (the_one_that_moves->pos_x - extern_destination->col) > 1;
	}
	else if ((extern_destination->fil == the_one_that_moves->pos_y) && (extern_destination->col > the_one_that_moves->pos_x)) { //Right
		my_direction = Direction_type::Right;
		*out_of_range = (extern_destination->col - the_one_that_moves->pos_x) > 1;
	}
	else if ((extern_destination->fil < the_one_that_moves->pos_y) && (extern_destination->col == the_one_that_moves->pos_x)) { //Jump_Straight
		my_direction = Direction_type::Jump_Straight;
		*out_of_range = (the_one_that_moves->pos_x - extern_destination->fil) != 2;
	}
	else if ((extern_destination->fil < the_one_that_moves->pos_y) && (extern_destination->col < the_one_that_moves->pos_x)) { //Jump_Left
		my_direction = Direction_type::Jump_Left;
		*out_of_range = ((the_one_that_moves->pos_x - extern_destination->fil) > 1) ||
						((the_one_that_moves->pos_y - extern_destination->col) != 2);
	}
	else if ((extern_destination->fil < the_one_that_moves->pos_y) && (extern_destination->col > the_one_that_moves->pos_x)) { //Jump_Right
		my_direction = Direction_type::Jump_Right;
		*out_of_range = ((the_one_that_moves->pos_x - extern_destination->col) > 1) ||
						((the_one_that_moves->pos_y - extern_destination->fil) != 2);
	}
	else
		my_direction = Direction_type::None;  //a stay still was received

	return my_direction;
}

bool Scene::check_attack(Action_info * Action_info_to_be_checked, bool proj_check) {

	bool is_the_attack_possible;
	Sense_type proj_sense;

	if (!proj_check)
		if (Action_info_to_be_checked->is_local || !data->my_network_data.is_client())
			Action_info_to_be_checked->my_character = Action_info_to_be_checked->is_local ? my_player : other_player;

	Player * the_one_that_attacks = get_player(Action_info_to_be_checked->my_character);
	Action_info_to_be_checked->id = the_one_that_attacks->id;
	if (Action_info_to_be_checked->is_local)
		proj_sense = the_one_that_attacks->get_sense();
	else{
		if ((Action_info_to_be_checked->final_pos_y == the_one_that_attacks->pos_y) &&
				(Action_info_to_be_checked->final_pos_x < the_one_that_attacks->pos_x)) { //Left
			proj_sense = Sense_type::Left;
			Action_info_to_be_checked->my_direction = Direction_type::Left;
		}
		else {  //Right
			proj_sense = Sense_type::Right;
			Action_info_to_be_checked->my_direction = Direction_type::Right;
		}
	}

	if (the_one_that_attacks->is_dead()){
		is_the_attack_possible = false;
		std::cout << " Error , el jugador que debería atacar está muerto" << std::endl;
	}
	else{
		int delta = (proj_sense == Sense_type::Left) ? -1 : 1;

		is_the_attack_possible = maps[actual_map]->cell_has_floor(the_one_that_attacks->pos_x + delta, the_one_that_attacks->pos_y);

		if (is_the_attack_possible && Action_info_to_be_checked->is_local) { //load the destination column and row in the eventpackage
			Action_info_to_be_checked->final_pos_y = the_one_that_attacks->pos_y;
			if (!proj_check) {
				int future_move = the_one_that_attacks->pos_x + delta * 3;
				if (future_move >= AMOUNT_COLS)
					Action_info_to_be_checked->final_pos_x = AMOUNT_COLS - 1;
				else if (future_move < 0)
					Action_info_to_be_checked->final_pos_x = 0;
				else
					Action_info_to_be_checked->final_pos_x = future_move;
			}
			else
				Action_info_to_be_checked->final_pos_x = the_one_that_attacks->pos_x + delta;

			Action_info_to_be_checked->my_direction = (proj_sense == Sense_type::Left) ? Direction_type::Left : Direction_type::Right;
		}
	}

	return is_the_attack_possible;
}

bool Scene::check_enemy_action(Action_info * package_to_be_analyze) {

	bool is_the_enemy_action_possible = false;
	Sense_type in_witch_direction_is_he_looking;
	Position extern_destination;
	Action_type action_to_be_checked;
	Direction_type my_direction;

	searched_id = package_to_be_analyze->id;
	Enemy* the_enemy_that_acts = *find_if(curr_enemies->begin(), curr_enemies->end(), char_meets_id);

	extern_destination.fil = package_to_be_analyze->final_pos_y;
	extern_destination.col = package_to_be_analyze->final_pos_x;
	action_to_be_checked = package_to_be_analyze->action;

	if (the_enemy_that_acts->is_dead())
	{
		std::cout << " Error , el monstruo que debería actuar está muerto" << std::endl;
		is_the_enemy_action_possible = false;
	}
	else
	{
		switch (action_to_be_checked)
		{
		case Action_type::Move:
			bool out_of_range;
			my_direction = load_direction(&extern_destination, the_enemy_that_acts, &out_of_range);

			switch (my_direction)
			{
			case Direction_type::Left:
			case Direction_type::Right:
			case Direction_type::Jump_Straight:
			case Direction_type::Jump_Left:
			case Direction_type::Jump_Right:
				is_the_enemy_action_possible = maps[actual_map]->cell_has_floor(extern_destination.col, extern_destination.fil);
				break;
			case Direction_type::None: //stay still was received
				is_the_enemy_action_possible = true;
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

bool Scene::check_if_has_to_fall(Character* charac) {

	bool has_to_fall = false;

	if (charac->has_to_fall()) {
		if (charac->pos_y < 10 &&
				maps[actual_map]->cell_has_floor(charac->pos_x, charac->pos_y + 1)) {
			has_to_fall = true;
		}
		else
			charac->dont_fall();
	}

	return has_to_fall;
}

Player * Scene::get_player(Item_type player_to_be_found) {

	Player * player_found = NULL;
	Item_type player_name = (*curr_players)[0]->get_printable();
	if (player_name == player_to_be_found)
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
	if (curr_enemy_to_act_on >= curr_enemies->size())
		curr_enemy_to_act_on = 0;

	Enemy* curr_enemy = curr_enemies->at(curr_enemy_to_act_on++);

	if (curr_enemy->is_iddle()) {
		enemy_action_info = curr_enemy->act();
		new_enemy_action = true;
		notify_obs();					//ScenarioEventsObserver
		new_enemy_action = false;
	}
	
	for(int i = 0; i < curr_enemies->size(); i++)
		curr_enemies->at(i)->ev_handler->handle_event();

}
void Scene::control_enemies() {
	for (int i = 0; i < curr_enemies->size(); i++) 
		curr_enemies->at(i)->ev_handler->handle_event();
}
void Scene::control_all_actions() {

	for (int i = 0; i < curr_players->size(); i++) {
		Player* curr_player = curr_players->at(i);
		if (check_if_has_to_fall(curr_player))
			curr_player->ev_handler->get_ev_gen()->append_new_event_front(new FELL_EventPackage());
		curr_player->ev_handler->handle_event();
	}
	for (int i = 0; i < curr_players->size(); i++) {
		Player* curr_player = curr_players->at(i);
		curr_player->ev_handler->handle_event();
	}

	vector<Proyectile*> to_be_deleted;
	for (int i = 0; i < curr_proyectiles->size(); i++) {
		Proyectile* curr = curr_proyectiles->at(i);
		curr->ev_handler->handle_event();
		if (curr->has_disappeared())
			to_be_deleted.push_back(curr);
	}

	for (vector<Proyectile*>::iterator it = to_be_deleted.begin(); it != to_be_deleted.end(); ++it) {
		maps[actual_map]->delete_from_map(*it);
		delete *it;
	}
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


void Scene::load_action_on_character(Action_info action) {

	if (action.my_info_header == Action_info_id::ENEMY_ACTION) {
		for (vector<Enemy*>::iterator it = curr_enemies->begin(); it != curr_enemies->end(); ++it)
			if ((*it)->id == action.id) {

				if (!action.is_local) {
					Position pos = { action.final_pos_y , action.final_pos_x };
					bool out_of_range = false;
					action.my_direction = load_direction(&pos, *it, &out_of_range);
				}
				(*it)->append_action_to_character(action);
			}
	}
	else 
		for (vector<Player*>::iterator it = curr_players->begin(); it != curr_players->end(); ++it)
			if((*it)->id == action.id)
				(*it)->append_action_to_character(action);


		
}

void Scene::load_action_on_projectile(Action_info action)
{
	Item_type player_type;

	if(action.is_local)		player_type = my_player;
	else	player_type = action.my_character;

	Player* curr_player = get_player(player_type);
	Sense_type curr_sense = curr_player->get_sense();
	maps[actual_map]->place_on_map(curr_player->pos_x, curr_player->pos_y, Item_type::SNOWBALL, curr_sense, this);
}

void Scene::append_new_auxilar_event(EventPackage * event_to_be_saved) {

	saved_events->push(event_to_be_saved);

}

EventPackage * Scene::front_auxiliar_event() {

	return saved_events->front();
}

void Scene::load_saved_event_r() {

	load_saved_event = true;
	notify_obs();
	load_saved_event = false;

}



