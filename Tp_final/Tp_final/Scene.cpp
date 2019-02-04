#include "Scene.h"
#include "general.h"
 
Scene::Scene():Observable(Observable_type::SCENARIO)
{
	//flags
	this->game_finished = false;
	this->game_started = false;
	this->check_local_action = false;		
	this->has_to_draw = false;
	this->enemys_ready = false;
	this->we_won = false;
	this->we_lost = false;

	this->assistant_queue = new std::queue<EventPackage*>;
	this->action_from_allegro = NULL;
	this->actual_map = 1;

}


Scene::~Scene()
{

}



void Scene::handle_movement(Character_id char_id, unsigned int id, Direction_type dir, Action_type action) {
	
}



void Scene::execute_action(EventPackage * action_to_be_executed)
{
	Event_type event_to_be_execute = action_to_be_executed->give_me_your_event_type();


	switch (event_to_be_execute)
	{
	case Event_type::MOVE:
		execute_move(action_to_be_executed);
		break;

	case Event_type::ATTACK:
		execute_attack(action_to_be_executed);

		break;

	case Event_type::ACTION_REQUEST:

		if (((ACTION_REQUEST_EventPackage *)action_to_be_executed)->give_me_the_action == Action_type::Move)
			execute_move(action_to_be_executed);
		else
			execute_attack(action_to_be_executed);

		break;

	case Event_type::ENEMY_ACTION:
		execute_enemy_action(action_to_be_executed);

		break;

	default:
		std::cout << "Error, Acción no ejecutable" << std::endl;
		break;

	}

//Lastly, we analyze the current game_situation
	if (this->both_players_dead())
	{
		this->we_lost = true;
		notify_obs();
		this->we_lost = false;
	}
	if ((!this->both_players_dead())&&(!this->any_monsters_left())&&(this->actual_map==10))
	{
		this->we_won = true;
		notify_obs();
		this->we_won = false;
	}
}

void Scene::execute_move(EventPackage * move_to_be_executed) {

}

void Scene::execute_attack(EventPackage * attack_to_be_executed) {

}

void Scene::execute_enemy_action(EventPackage * enemy_action_to_be_executed) {


}


void Scene::load_new_map(bool is_client, EventPackage* map_to_be_checked=NULL) {


		Map * new_map = new Map(12, 16);

	if (is_client) //The map came by networking, already checked
	{	
		//esto es lo que tenias antes, que por ahora no se condice con lo que programe de Map. despues coordinar conmigo para que esto funke.
		//Map * new_map = new Map(12, 16, ((MAP_IS_EventPackage*)map_to_be_checked)->give_me_the_map(), ((MAP_IS_EventPackage*)map_to_be_checked)->give_me_the_checksum());
		//por que no meter todo esto en el constructor?
		new_map->load_on_map((const char*)(((MAP_IS_EventPackage*)map_to_be_checked)->give_me_the_map()));
		new_map->load_checksum(((MAP_IS_EventPackage*)map_to_be_checked)->give_me_the_checksum());
		
		this->actual_map++;
	}
	else
	{	//I´m server, I´ve the map available
		new_map->load_on_map(give_me_the_CSV(actual_map));
		new_map->load_checksum(this->make_checksum(give_me_the_CSV(actual_map)));
		//maps->push_back(new Map(12, 16, give_me_the_CSV(actual_map),this->make_checksum(give_me_the_CSV(actual_map))));
	}

		maps.push_back(new_map);

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

EventPackage* Scene::give_me_my_enemy_action(bool is_initializing){

	EventPackage* my_enemy_action_event = NULL;

	my_enemy_action_event=maps.at(this->actual_map)->give_me_my_enemy_action(is_initializing);

	if (my_enemy_action_event == NULL) //ENEMYS_LOADED MUST BE SENT
	{
		bool enemys_ready=true;
		notify_obs();
		bool enemys_ready = true;
	}


	return my_enemy_action_event;
}




void Scene::gameInit() {	

	this->game_started = true;	//indica que todo inicializo correctamente y entonces debe empezar a funcionar la FSM.
	notify_obs();
	this->game_started = false;

}


EventPackage * Scene::give_me_my_allegro_event() {
	return this->action_from_allegro;
}

Item_type Scene::give_me_my_player() {

	return this-> my_player;
}
Item_type Scene::give_the_other_player() {

	return this->other_player;
}

void Scene::set_new_allegro_event(EventPackage * new_event) {
	 this->action_from_allegro= new_event;
}

bool Scene::both_players_dead()
{
	std::vector<Player*>* players = maps[actual_map]->get_all_players();
	bool all_dead = true;
	for (int i = 0; i < players->size(); i++) 
		if (!players->at(i)->is_dead()) {
			all_dead = false;
			break;
		}
	return all_dead;
}

bool Scene::any_monsters_left()
{
	std::vector<Enemy*>* monsters = maps[actual_map]->get_all_enemies();

	bool any_left = false;
	for (int i = 0; i < monsters->size(); i++)
		if (!monsters->at(i)->is_dead()) {
			any_left = true;
			break;
		}

	return any_left;
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

	bool is_the_action_possible;
	Event_type event_to_be_analyze = package_to_be_analyze->give_me_your_event_type();


	switch (event_to_be_analyze)
	{
	case Event_type::MOVE:

		is_the_action_possible=check_move(package_to_be_analyze);
		break;

	case Event_type::ATTACK:

		is_the_action_possible = check_attack(package_to_be_analyze);
		break;

	case Event_type::ACTION_REQUEST:

		if(((ACTION_REQUEST_EventPackage *)package_to_be_analyze)->give_me_the_action==Action_type::Move)
			is_the_action_possible = check_move(package_to_be_analyze);
		else
			is_the_action_possible = check_attack(package_to_be_analyze);

		break;

	case Event_type::ENEMY_ACTION:
		is_the_action_possible = check_enemy_action(package_to_be_analyze);
		break;

	default:
		std::cout << "Acción no analizable" << std::endl;
		break;
	
	}
		

	return is_the_action_possible;
}

bool Scene::check_move(EventPackage * package_to_be_analyze ) {

	bool is_the_move_possible;
	bool is_local;
	MOVE_EventPackage* my_event_package = ((MOVE_EventPackage *)package_to_be_analyze);
	Player * the_one_that_moves = NULL;
	Position extern_destination;
	Position local_destination;
	Direction_type my_direction;

	if (package_to_be_analyze->is_this_a_local_action())
	{
		is_local = true;
		my_event_package->set_character((Character_type)my_player);
		the_one_that_moves = get_player(my_player);
		my_direction = my_event_package->give_me_your_direction();
	}
	else
	{
		is_local = false;
		my_event_package->set_character((Character_type)other_player);
		the_one_that_moves = get_player(other_player);
		extern_destination.fil = my_event_package->give_me_your_destination_row();
		extern_destination.col = my_event_package->give_me_your_destination_column();

		if ((extern_destination.fil == the_one_that_moves->pos_x) && (extern_destination.col < the_one_that_moves->pos_y)) //Left
			my_direction = Direction_type::Left;
		else if ((extern_destination.fil == the_one_that_moves->pos_x) && (extern_destination.col > the_one_that_moves->pos_y)) //Right
			my_direction = Direction_type::Right;
		else if ((extern_destination.fil < the_one_that_moves->pos_x) && (extern_destination.col == the_one_that_moves->pos_y)) //Jump_Straight
			my_direction = Direction_type::Jump_Straight;
		else if ((extern_destination.fil < the_one_that_moves->pos_x) && (extern_destination.col < the_one_that_moves->pos_y)) //Jump_Left
			my_direction = Direction_type::Jump_Left;
		else if ((extern_destination.fil < the_one_that_moves->pos_x) && (extern_destination.col > the_one_that_moves->pos_y)) //Jump_Right
			my_direction = Direction_type::Jump_Right;
	}



	if (the_one_that_moves->is_dead())
	{
		is_the_move_possible = false;
		std::cout << " Error , el jugador que debería moverse está muerto" << std::endl;

	}
	else
	{

		switch (my_direction)
		{
		case Direction_type::Left:
			if (is_local)
			{
				if (maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x , the_one_that_moves->pos_y - 1))
					is_the_move_possible = false;
				else
				{
					is_the_move_possible = true;
					local_destination.fil = the_one_that_moves->pos_x;
					local_destination.col = the_one_that_moves->pos_y - 1;
				}
			}
			else
			{
				if (maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col - 1))
					is_the_move_possible = false;
				else
					is_the_move_possible = true;
			}

			break;

		case Direction_type::Right:
			if (is_local)
			{
				if (maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x , the_one_that_moves->pos_y + 1))
					is_the_move_possible = false;
				else
				{
					is_the_move_possible = true;
					local_destination.fil = the_one_that_moves->pos_x;
					local_destination.col = the_one_that_moves->pos_y + 1;
				}
			}
			else
			{
				if (maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col + 1))
					is_the_move_possible = false;
				else
					is_the_move_possible = true;
			}
			break;

		case Direction_type::Jump_Straight: //creo que nunca tengo que chequear esto, no hay ningún caso donde no pueda saltar para arriba. como mucho vuelvo a caer
			break;

		case Direction_type::Jump_Left:
			if (is_local)
			{
				if (maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x - 1, the_one_that_moves->pos_y - 1) && maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x - 2, the_one_that_moves->pos_y - 1))
				{
					my_event_package->set_direction(Direction_type::Jump_Straight);
					is_the_move_possible = true;
				}
				else
				{
					is_the_move_possible = true;
					local_destination.fil = the_one_that_moves->pos_x - 2;
					local_destination.col = the_one_that_moves->pos_y - 1;
				}
			}
			else
			{
				if ((maps[actual_map]->cell_has_floor(extern_destination.fil - 1, extern_destination.col - 1)) && (maps[actual_map]->cell_has_floor(extern_destination.fil - 2, extern_destination.col - 1)))
				{
					is_the_move_possible = false; //can´t be fixed, extern move received must be valid
				}
				else
					is_the_move_possible = true;
			}
			break;

		case Direction_type::Jump_Right:
			if (is_local)
			{
				if (maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x - 1, the_one_that_moves->pos_y + 1) && maps[actual_map]->cell_has_floor(the_one_that_moves->pos_x - 2, the_one_that_moves->pos_y + 1))
				{
					my_event_package->set_direction(Direction_type::Jump_Straight);
					is_the_move_possible = true;
				}
				else
				{
					is_the_move_possible = true;
					local_destination.fil = the_one_that_moves->pos_x - 2;
					local_destination.col = the_one_that_moves->pos_y + 1;
				}
			}
			else
			{
				if ((maps[actual_map]->cell_has_floor(extern_destination.fil - 1, extern_destination.col + 1)) && (maps[actual_map]->cell_has_floor(extern_destination.fil - 2, extern_destination.col + 1)))
				{
					is_the_move_possible = false; //can´t be fixed, extern move received must be valid
				}
				else
					is_the_move_possible = true;
			}
			break;

		default:
			std::cout << " Error , no se recibió un MOVE para analizar" << std::endl;
			break;
		}
	}

	if (is_the_move_possible && is_local) //load the destination column and row in the eventpackage
	{
		my_event_package->set_destination_row(local_destination.fil);
		my_event_package->set_destination_column(local_destination.col);

	}

	return is_the_move_possible;
}
bool Scene::check_attack(EventPackage * package_to_be_analyze) {

	bool is_the_attack_possible;
	bool is_local;
	ATTACK_EventPackage* my_event_package = ((ATTACK_EventPackage *)package_to_be_analyze);
	Player * the_one_that_attack = NULL;
	Sense_type in_witch_direction_is_he_looking;
	Position extern_destination;
	Position local_destination;



	if (package_to_be_analyze->is_this_a_local_action())
	{
		is_local = true;
		the_one_that_attack = get_player(my_player);
		in_witch_direction_is_he_looking = the_one_that_attack->get_sense();
	}
	else
	{
		is_local = false;
		the_one_that_attack = get_player(other_player);
		extern_destination.fil = my_event_package->give_me_your_destination_row();
		extern_destination.col = my_event_package->give_me_your_destination_column();

		if ((extern_destination.fil == the_one_that_attack->pos_x) && (extern_destination.col < the_one_that_attack->pos_y)) //Left
			in_witch_direction_is_he_looking = Sense_type::Left;
		else  //Right
			in_witch_direction_is_he_looking = Sense_type::Right;
	}


	if (the_one_that_attack->is_dead())
	{
		is_the_attack_possible = false;
		std::cout << " Error , el jugador que debería atacar está muerto" << std::endl;
	}
	else
	{
		if (in_witch_direction_is_he_looking == Sense_type::Left)
		{
			if (is_local)
			{
				if (maps[actual_map]->cell_has_floor(the_one_that_attack->pos_x, the_one_that_attack->pos_y -1))
					is_the_attack_possible = false;
				else
				{
					is_the_attack_possible = true;
					local_destination.fil = the_one_that_attack->pos_x;
					local_destination.col = the_one_that_attack->pos_y - 1;
				}
			}
			else
			{
				if (maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col - 1))
					is_the_attack_possible = false;
				else
					is_the_attack_possible = true;
			}
		}
		else //Sense_type::Right
		{
			if (is_local)
			{
				if (maps[actual_map]->cell_has_floor(the_one_that_attack->pos_x, the_one_that_attack->pos_y + 1))
					is_the_attack_possible = false;
				else
				{
					is_the_attack_possible = true;
					local_destination.fil = the_one_that_attack->pos_x;
					local_destination.col = the_one_that_attack->pos_y + 1;
				}
			}
			else
			{
				if (maps[actual_map]->cell_has_floor(extern_destination.fil, extern_destination.col + 1))
					is_the_attack_possible = false;
				else
					is_the_attack_possible = true;
			}
		}

	}
	if (is_the_attack_possible && is_local) //load the destination column and row in the eventpackage
	{
		my_event_package->set_destination_row(local_destination.fil);
		my_event_package->set_destination_column(local_destination.col);

	}
	return is_the_attack_possible;
}


bool Scene::check_enemy_action(EventPackage * package_to_be_analyze) {

	bool is_the_enemy_action_possible;
	bool is_local;
	ENEMY_ACTION_EventPackage* my_event_package = ((ENEMY_ACTION_EventPackage *)package_to_be_analyze);
	Enemy * the_enemy_that_acts = NULL;
	Sense_type in_witch_direction_is_he_looking;
	Position extern_destination;
	Action_type action_to_be_checked;
	Direction_type my_direction;

	if (package_to_be_analyze->is_this_a_local_action())
	{
		is_local = true;
		std::cout << "Error, Un EA local no debería chequearse nunca" << std::endl;
		std::cout << "NO SE CHEQUEO NADA, ERROR" << std::endl;
		is_the_enemy_action_possible = false;

	}
	else
	{
		is_local = false;
		the_enemy_that_acts = get_enemy(my_event_package->give_me_the_monsterID);
		extern_destination.fil = my_event_package->give_me_the_destination_row();
		extern_destination.col = my_event_package->give_me_the_destination_column();
		action_to_be_checked = my_event_package->give_me_the_action();


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

				if ((extern_destination.fil == the_enemy_that_acts->pos_x) && (extern_destination.col < the_enemy_that_acts->pos_y)) //Left
					my_direction = Direction_type::Left;
				else if ((extern_destination.fil == the_enemy_that_acts->pos_x) && (extern_destination.col > the_enemy_that_acts->pos_y)) //Right
					my_direction = Direction_type::Right;
				else if ((extern_destination.fil < the_enemy_that_acts->pos_x) && (extern_destination.col == the_enemy_that_acts->pos_y)) //Jump_Straight
					my_direction = Direction_type::Jump_Straight;
				else if ((extern_destination.fil < the_enemy_that_acts->pos_x) && (extern_destination.col < the_enemy_that_acts->pos_y)) //Jump_Left
					my_direction = Direction_type::Jump_Left;
				else if ((extern_destination.fil < the_enemy_that_acts->pos_x) && (extern_destination.col > the_enemy_that_acts->pos_y)) //Jump_Right
					my_direction = Direction_type::Jump_Right;
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

				case Direction_type::Jump_Straight: //creo que nunca tengo que chequear esto, no hay ningún caso donde no pueda saltar para arriba. como mucho vuelvo a caer
					break;

				case Direction_type::Jump_Left:

						if ((maps[actual_map]->cell_has_floor(extern_destination.fil - 1, extern_destination.col - 1)) && (maps[actual_map]->cell_has_floor(extern_destination.fil - 2, extern_destination.col - 1)))
						{
							is_the_enemy_action_possible = false; //can´t be fixed, extern move received must be valid
						}
						else
							is_the_enemy_action_possible = true;				
					break;

				case Direction_type::Jump_Right:

						if ((maps[actual_map]->cell_has_floor(extern_destination.fil - 1, extern_destination.col + 1)) && (maps[actual_map]->cell_has_floor(extern_destination.fil - 2, extern_destination.col + 1)))
						{
							is_the_enemy_action_possible = false; //can´t be fixed, extern move received must be valid
						}
						else
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
	}

	return is_the_enemy_action_possible;
}


Player * Scene::get_player(Item_type player_to_be_found) {

	Player * player_found = NULL;
	std::vector<Player*>* my_vector_of_players= maps[actual_map]->get_all_players();

	if ((*my_vector_of_players)[0]->get_printable() == player_to_be_found)
		player_found = (*my_vector_of_players)[0];
	else
		player_found = (*my_vector_of_players)[1];

	return player_found;
}

Enemy * Scene::get_enemy(uchar enemy_to_be_found) {

	Enemy * enemy_found = NULL;
	std::vector<Enemy*>* my_vector_of_enemys = maps[actual_map]->get_all_enemies();

	for (int i = 0; i < my_vector_of_enemys->size(); i++)
	{
		if ((*my_vector_of_enemys)[0]->id == enemy_to_be_found)
			enemy_found = (*my_vector_of_enemys)[0];
	}


	return enemy_found;
}

bool Scene::did_we_win(EventPackage * package_to_be_analyze)
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

bool Scene::did_we_lose(EventPackage * package_to_be_analyze)
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



bool Scene::do_you_have_to_draw() {

	return this->has_to_draw;
}

void Scene::append_new_auxilar_event(EventPackage* new_ev_pack) {
	assistant_queue->push(new_ev_pack);
}