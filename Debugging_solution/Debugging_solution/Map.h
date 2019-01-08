#pragma once
#include "MapCell.h"
#include "MapThingFactory.h"
#include <vector>

class Map
{
public:
	Map(int number_of_rows, int number_of_columns);
	~Map();

	bool cell_has_proyectiles(int coord_x, int coord_y);
	std::vector<Proyectile*> get_cell_proyectiles(int coord_x, int coord_y);

	bool cell_has_players(int coord_x, int coord_y);
	std::vector<Player*> get_cell_players(int coord_x, int coord_y);

	bool cell_has_enemies(int coord_x, int coord_y);
	std::vector<Enemy*> get_cell_enemies(int coord_x, int coord_y);
	
	MapThing* get_from_map(unsigned int id);

	bool move_id(unsigned int id, int final_x, int final_y);
	void place_on_map(int coord_x, int coord_y, MapThing* thing);

	void print_map();
	int get_max_number_of_floors();

	void load_on_map(char* map_string);
	void reset_map();

private:
	MapCell ** map_cells;
	MapCell *get_cell(int coord_x, int coord_y);

	bool delete_from_map(unsigned int id);

	int number_of_rows;
	int number_of_columns;
};