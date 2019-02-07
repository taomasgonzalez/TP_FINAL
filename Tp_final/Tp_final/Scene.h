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
	Scene();
	~Scene();
	void gameInit();

	void handle_movement(Character_id char_id, unsigned int id, Direction_type dir, Action_type action);

	//Analyze of gaming situations
	bool is_the_action_possible(Event_type event_to_be_checked, Action_info * package_to_be_analyze); //wrap for a clearer implementation of check_Action

	//generadas por tommy para hacer mas facil el manejo de mapas
	bool both_players_dead();
	bool any_monsters_left();
	bool did_we_win();  //I´m client, analyze if the game was won by the players
	bool did_we_lose(); //I´m client, analyze if the game was lost by the players
	bool check_current_game_situation();


	//Executing functions
	void execute_action(EventPackage * action_to_be_executed);

	void finish_game();

	//Getters
	//EventPackage * give_me_my_allegro_event();
	Item_type give_me_my_player();
	Item_type give_the_other_player();
	const char * give_me_the_CSV(unsigned int actual_map);
	Player * get_player(Item_type player_to_be_found);
	Action_info * give_me_my_enemy_action(bool is_initializing);

	//Control Flags getters
	bool game_is_finished();
	bool do_you_have_to_draw();

	//map functions
	void load_new_map(bool is_client, const char * the_map =NULL, char the_checksum=NULL );
	bool is_the_map_okay(const char * the_map , char the_checksum );

	void set_new_allegro_event(EventPackage * new_event);


	std::vector <Map*> maps;
	//std::vector<Map*>::iterator actual_map;  //aprender a usarlo bien
	unsigned int actual_map;


	//flags
	bool game_started;
	bool game_finished;
	bool initializing;
	bool enemys_ready;
	bool we_lost;
	bool we_won;
	bool check_local_action;		//see where this flag is turn on or off
	bool has_to_draw;

	bool new_enemy_action;
	void append_new_auxilar_event(Action_info* new_ev_pack_info);
	
	std::queue<Action_info*>* assistant_queue;

	/*nuevas funciones de timer para los enemies, agregadas por tommy
	esto estaria bueno despues wrappearlo todo en allegroClass, pero por ahora SE QUEDA TODO ACA.
	*/
	void control_enemy_actions();
	void control_proyectile_actions();

	Position shortest_movement_2_nearest_player(PurpleGuy* purple_guy);

private:

	unsigned char make_checksum(const char * CSV_map_location);
	//checkes
	bool check_move(EventPackage * package_to_be_analyze);
	bool check_attack(EventPackage * package_to_be_analyze);
	bool check_enemy_action(EventPackage * package_to_be_analyze);
	//executers
	void execute_move(EventPackage * move_to_be_executed);
	void execute_attack(EventPackage * attack_to_be_executed);
	void execute_enemy_action(EventPackage * enemy_action_to_be_executed);

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
	ALLEGRO_EVENT_QUEUE * enemy_actions_queue = al_create_event_queue();
	ALLEGRO_EVENT_QUEUE * proyectile_actions_queue = al_create_event_queue();

	Enemy* get_enemy_to_act_on(ALLEGRO_TIMER* timer);
	Proyectile* get_proyectile_to_act_on(ALLEGRO_TIMER* timer);
	Action_info* enemy_action_info;

	Player* find_nearest_player(int pos_x, int pos_y);
};

