#pragma once

#include "MapCell.h"
#include "Enemy.h"
#include "Player.h"
#include "Fireball.h"
#include "MapThingFactory.h"
#include "DijkstraMachine.h"
#include <vector>

using namespace std;

class Map
{
public:
	Map(unsigned int number_of_rows, unsigned int number_of_columns, Userdata* data);
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
	void place_on_map(int coord_x, int coord_y, Item_type identifyer, Sense_type direction, void * obs_info = NULL);

	void print_map();
	int get_max_number_of_floors();

	//llamar despues de construir al mapa para cargar las cosas!!
	void load_on_map(const unsigned char* map_string, void* scenario = NULL);

	void load_checksum(unsigned char checksum);

	void reset_map();

	bool delete_from_map(unsigned int id);
	bool delete_from_map(MapThing* thing);
	const unsigned char * give_me_the_original_map();
	unsigned char give_me_the_checksum();

	Action_info get_initial_enemy_actions();

	void print_cell(int coord_x, int coord_y);

	const char* get_last_loaded_distribution();

	Position find_next_movement_4_shortest_path(int from_x, int from_y, int to_x, int to_y);

	int get_number_of_rows();
	int get_number_of_columns();

	void append_graphic_facility(void* drawer);
private:
	MapCell* get_cell(unsigned int coord_x, unsigned int coord_y);
	MapCell ** map_cells;

	unsigned int number_of_rows;
	unsigned int number_of_columns;
	unsigned char my_checksum;


	string original_distribution;
	MapThing* get_from_map(unsigned int coord_x, unsigned int coord_y, unsigned int coord_z);

	void place_on_map(unsigned int coord_x, unsigned int coord_y, MapThing* thing);
	
	void clear();


	std::vector<Proyectile*>* all_proyectiles = NULL;
	std::vector<Player*>* all_players = NULL;
	std::vector<Enemy*>* all_enemies = NULL;

	void delete_from_map_thing_vectors(MapThing* thing);
	void place_on_map_thing_vectors(MapThing* thing);

	MapThingFactory map_filler;

	//should perform a call to load_on_map to create the dijkstra_manager.
	MapDijkstraMachine *dijkstra_manager = NULL;

};