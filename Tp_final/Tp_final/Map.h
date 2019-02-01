#pragma once
#include "MapCell.h"
#include "MapThingFactory.h"
#include <vector>

class Map
{
public:
	Map(int number_of_rows, int number_of_columns);
	~Map();

	std::vector<Proyectile*> get_all_proyectiles();
	std::vector<Player*> get_all_players();
	std::vector<Enemy*> get_all_enemies();



	bool cell_has_proyectiles(int coord_x, int coord_y);
	std::vector<Proyectile*> get_cell_proyectiles(int coord_x, int coord_y);

	bool cell_has_players(int coord_x, int coord_y);
	std::vector<Player*> get_cell_players(int coord_x, int coord_y);

	bool cell_has_enemies(int coord_x, int coord_y);
	std::vector<Enemy*> get_cell_enemies(int coord_x, int coord_y);

	MapThing* get_from_map(unsigned int id);
	MapThing* get_from_map(int coord_x, int coord_y, int coord_z);

	bool move_id(unsigned int id, int final_x, int final_y);
	void place_on_map(int coord_x, int coord_y, MapThing* thing);

	void print_map();
	int get_max_number_of_floors();

	//llamar despues de construir al mapa para cargar las cosas!!
	void load_on_map(const char* map_string);

	void reset_map();

	bool delete_from_map(unsigned int id);
	bool delete_from_map(MapThing* thing);

	void print_cell(int coord_x, int coord_y);

	const char* get_last_loaded_distribution();


private:
	MapCell * * map_cells;
	MapCell get_cell(int coord_x, int coord_y);

	int number_of_rows;
	int number_of_columns;

	const char* original_distribution;

	void clear();
};