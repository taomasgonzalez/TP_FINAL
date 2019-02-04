#pragma once
#include "MapCell.h"
#include "Enemy.h"
#include "Player.h"
#include "Fireball.h"
#include "EventPackage.h"
#include "MapThingFactory.h"
#include <vector>

class Map
{
public:
	Map(int number_of_rows, int number_of_columns);
	~Map();


	std::vector<Proyectile*>* get_all_proyectiles();
	std::vector<Player*>* get_all_players();
	std::vector<Enemy*>* get_all_enemies();

	bool cell_has_proyectiles(int coord_x, int coord_y);
	std::vector<Proyectile*> get_cell_proyectiles(int coord_x, int coord_y);

	bool cell_has_players(int coord_x, int coord_y);
	std::vector<Player*> get_cell_players(int coord_x, int coord_y);

	bool cell_has_enemies(int coord_x, int coord_y);
	std::vector<Enemy*> get_cell_enemies(int coord_x, int coord_y);

	bool cell_has_enemy_proyectiles(int coord_x, int coord_y);
	bool cell_has_player_proyectiles(int coord_x, int coord_y);

	bool cell_has_floor(int coord_x, int coord_y);

	MapThing* get_from_map(unsigned int id);

	bool move_id(unsigned int id, int final_x, int final_y);
	bool move_map_thing(MapThing* thing, int final_x, int final_y);

	//creates a new MapThing object and places it on the map.
	void place_on_map(int coord_x, int coord_y, Item_type identifyer, Sense_type direction);

	void print_map();
	int get_max_number_of_floors();

	//llamar despues de construir al mapa para cargar las cosas!!
	void load_on_map(const char* map_string);
	void register_enemies_event_queue(ALLEGRO_EVENT_QUEUE * enemies_ev_queue);
	void load_checksum(unsigned char checksum);

	void reset_map();

	bool delete_from_map(unsigned int id);
	bool delete_from_map(MapThing* thing);
	const char * give_me_the_original_map();
	unsigned char give_me_the_checksum();
	EventPackage* give_me_my_enemy_action(bool is_initializing);


	void print_cell(int coord_x, int coord_y);

	const char* get_last_loaded_distribution();

private:
	MapCell get_cell(int coord_x, int coord_y);
	MapCell * * map_cells;

	int number_of_rows;
	int number_of_columns;
	unsigned char my_checksum;


	const char* original_distribution;
	MapThing* get_from_map(int coord_x, int coord_y, int coord_z);

	void place_on_map(int coord_x, int coord_y, MapThing* thing);
	
	void clear();


	std::vector<Proyectile*>* all_proyectiles = NULL;
	std::vector<Player*>* all_players = NULL;
	std::vector<Enemy*>* all_enemies = NULL;

	void delete_from_map_thing_vectors(MapThing* thing);
	void place_on_map_thing_vectors(MapThing* thing);

	MapThingFactory map_filler;
};