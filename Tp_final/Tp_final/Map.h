#pragma once
#include "MapCell.h"
#include "Enemy.h"
#include "Player.h"
#include "Fireball.h"
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
	bool place_on_map(int coord_x, int coord_y, MapThing* thing);

private:
	MapCell ** map_cells;
	MapCell get_cell(int coord_x, int coord_y);

	bool delete_from_map(unsigned int id);

	int number_of_rows;
	int number_of_columns;
};