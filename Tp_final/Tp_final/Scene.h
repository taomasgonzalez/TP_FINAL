#pragma once
#include "Userdata.h"
#include "Allegroclass.h"
#include "general.h"
#include "Observable.h"
#include "Map.h"
#include <iostream>

/*******************************************************************************
							ENUM CLASS STATE_TYPE
******************************************************************************/
class Scene : public Observable
{
public:
	Scene(Userdata* data, Item_type my_player, Item_type his_player);
	~Scene();

	void gameInit();

/*******************************************************************************
	STATE OF THE GAME
******************************************************************************/
	//generadas por tommy para hacer mas facil el manejo de mapas
	bool both_players_dead();
	bool any_monsters_left();
	bool did_we_win();  //I´m client, analyze if the game was won by the players
	bool did_we_lose(); //I´m client, analyze if the game was lost by the players

	bool game_is_finished();
	void finish_game();			//ends the game

	//Getters

	//player information
	Item_type give_me_my_player();
	Item_type give_the_other_player();
	Player * get_player(Item_type player_to_be_found);

	//map information
	const char * give_me_the_CSV(unsigned int actual_map);
	const char * give_me_the_map_info();
	Action_info give_me_my_enemy_action(bool is_initializing);

/*******************************************************************************
	MOVEMENTS
******************************************************************************/
	void handle_movement(Character_id char_id, unsigned int id, Direction_type dir, Action_type action);

	//checkers
	bool check_if_has_to_fall(unsigned int id);
	bool check_position(Action_info position_info);
	void check_current_game_situation();
	bool is_the_action_possible(Action_info * package_to_be_analyze); //wrap for a clearer implementation of check_Action

	//Executing functions
	void execute_action(Action_info * action_to_be_executed, bool & should_be_hit);
	void execute_proyectile(Proyectile* proyectile_to_be_executed, bool & should_hit);
	Position shortest_movement_2_nearest_player(PurpleGuy* purple_guy);

	/*nuevas funciones de timer para los enemies, agregadas por tommy
	esto estaria bueno despues wrappearlo todo en allegroClass, pero por ahora SE QUEDA TODO ACA.
	*/
	void control_enemy_actions();
	void control_proyectile_actions();

/*******************************************************************************
	OPERATING OVER MAPS
******************************************************************************/

	void load_new_map(bool is_client, const char * the_map =NULL, char the_checksum=NULL );
	bool is_the_map_okay(const char * the_map , char the_checksum );
	void load_new_graphic_level();

	std::vector <Map*> maps;
	int actual_map;

	void load_action_on_character(Action_info action);

/*******************************************************************************
	FLAGS FOR OBSERVERS
******************************************************************************/
	bool game_started = false;
	bool game_finished = false;
	bool initializing = false;
	bool enemys_ready = false;
	bool we_lost = false;
	bool we_won = false;
	bool check_local_action = false;		//see where this flag is turn on or off
	bool new_enemy_action = false;
	bool load_action_on_char = false;
	bool should_hit = false;
	bool load_graphic_level = false;

	void append_new_auxilar_event(Action_info new_action_info);
	
	std::queue<Action_info>* assistant_queue;


	void append_graphic_facility(void* drawer);
	unsigned int get_action_to_be_loaded_id();
	Action_info get_action_to_be_loaded();

private:
	void * graphics = NULL;

	unsigned char make_checksum(const char * CSV_map_location);

	//checkers
	bool check_move(Action_info * package_to_be_analyze);
	Direction_type load_direction(Position * extern_destination, Character* the_one_that_moves);
	bool check_attack(Action_info * package_to_be_analyze);
	bool check_enemy_action(Action_info * package_to_be_analyze);

	//executers
	void execute_move(Action_info * move_to_be_executed, bool & should_die);
	void execute_attack(Action_info * attack_to_be_executed);
	void execute_enemy_action(Action_info * enemy_action_to_be_executed, bool & should_be_hit);

	//EventPackage* action_from_allegro; //se lo guarda cuando se llama a draw, no esta chequeado. Se lo manda despues a ScenarioEventsObserver::update() para chquearlo
	
	unsigned int points;
	Item_type my_player;
	Item_type other_player;

	std::vector<Player*>* curr_players;
	std::vector<Enemy*>* curr_enemies;
	std::vector<Proyectile*>* curr_proyectiles;

	
	/*nuevas funciones de timer para los enemies, agregadas por tommy
	esto estaria bueno despues wrappearlo todo en allegroClass, pero por ahora SE QUEDA TODO ACA. 
	*/
	ALLEGRO_EVENT_QUEUE * enemy_actions_queue = NULL;
	ALLEGRO_EVENT_QUEUE * proyectile_actions_queue = NULL;

	Enemy* get_enemy_to_act_on(ALLEGRO_TIMER* timer);
	Proyectile* get_proyectile_to_act_on(ALLEGRO_TIMER* timer);
	Action_info enemy_action_info;

	Player* find_nearest_player(int pos_x, int pos_y);

	Userdata* data; 
	unsigned int action_to_be_loaded_id;
	Action_info action_to_be_loaded;

};

