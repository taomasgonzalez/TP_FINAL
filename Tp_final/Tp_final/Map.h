#pragma once
#include "MapCell.h"
#include "Enemy.h"
#include "Player.h"
#include "Fireball.h"
//#include ""


class Map
{
public:
	Map(int number_of_rows, int number_of_columns);
	~Map();

	bool cell_has_proyectiles(int coord_x, int coord_y);
	bool cell_has_players(int coord_x, int coord_y);
	bool cell_has_enemies(int coord_x, int coord_y);

	//Enemy* get_cell_enemies(int coord_x, int coord_y);
	//Proyectile* get_cell_proyectiles(int coord_x, int coord_y);
	//Player* get_cell_players(int coord_x, int coord_y);

private:
	MapCell ** map_cells;
	MapCell get_cell(int coord_x, int coord_y);

};