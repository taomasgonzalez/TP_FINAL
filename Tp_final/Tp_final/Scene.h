#pragma once
#include "Userdata.h"
#include "Allegroclass.h"
#include "EventPackage.h"
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
	Scene();
	~Scene();
	void gameInit();

	void handle_movement(Character_id char_id, unsigned int id, Direction_type dir, Action_type action);

	//Analyze of gaming situations
	bool is_the_action_possible(EventPackage* package_to_be_analyze); //wrap for a clearer implementation of check_Action

	//generadas por tommy para hacer mas facil el manejo de mapas
	bool both_players_dead();
	bool any_monsters_left();
	bool did_we_win(EventPackage * package_to_be_analyze);  //I´m client, analyze if the game was won by the players
	bool did_we_lose(EventPackage * package_to_be_analyze); //I´m client, analyze if the game was lost by the players

	//Executing functions
	void execute_action(EventPackage * action_to_be_executed);

	void finish_game();

	//Getters
	EventPackage * give_me_my_allegro_event();
	Item_type give_me_my_player();
	Item_type give_the_other_player();
	const char * give_me_the_CSV(unsigned int actual_map);
	EventPackage* give_me_my_enemy_action(bool is_initializing);
	Player * get_player(Item_type player_to_be_found);



	//Control Flags getters
	bool game_is_finished();
	bool do_you_have_to_draw();

	//map functions
	void load_new_map(bool is_client, EventPackage* map_to_be_checked = NULL);
	bool is_the_map_okay(EventPackage * map_to_be_checked);
	unsigned char make_checksum(const char * CSV_map_location);


	void set_new_allegro_event(EventPackage * new_event);


	std::vector <Map*> maps;
	//std::vector<Map*>::iterator actual_map;  //aprender a usarlo bien
	unsigned int actual_map;

	bool game_started;
	bool game_finished;
	bool initializing;
	bool enemys_ready;
	bool we_lost;
	bool we_won;
	//para chequear un evento INTERNO de allegro por ejemplo, se usa en ScenarioEventsObserver::update()
	//hay que prenderlo y hacer notify_obs de scene cuando se levante un evento de allegro, tiene que estar cargado ese
	//evento de allegro convertido en eventpackage en Scene::Package* action_from_allegro;
	bool check_local_action;		//see where this flag is turn on or off
	bool has_to_draw;

	void append_new_auxilar_event(EventPackage* new_ev_pack);
	std::queue<EventPackage*>* assistant_queue;

private:
	//checkes
	bool check_move(EventPackage * package_to_be_analyze);
	bool check_attack(EventPackage * package_to_be_analyze);
	bool check_enemy_action(EventPackage * package_to_be_analyze);
	//executers
	void execute_move(EventPackage * move_to_be_executed);
	void execute_attack(EventPackage * attack_to_be_executed);
	void execute_enemy_action(EventPackage * enemy_action_to_be_executed);

	EventPackage* action_from_allegro; //se lo guarda cuando se llama a draw, no esta chequeado. Se lo manda despues a ScenarioEventsObserver::update() para chquearlo
	unsigned int points;
	Item_type my_player;
	Item_type other_player;

	std::vector<Player*>* curr_players;
	std::vector<Enemy*>* curr_enemies;
	std::vector<Proyectile*>* curr_proyectiles;

};

