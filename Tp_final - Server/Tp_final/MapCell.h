#pragma once
#include "Enemy.h"
#include "Player.h"
#include "SnowBall.h"
#include "Fireball.h"
#include <vector>

class MapCell
{
public:
	MapCell();
	~MapCell();

	bool has_enemies();
	std::vector<Enemy*> get_enemies();

	bool has_players();
	std::vector<Player*> get_players();

	bool has_proyectiles();
	std::vector<Proyectile*> get_proyectiles();

	MapThing * get_id(unsigned int wanted_id);
	bool delete_id(unsigned int wanted_id);
	bool delete_map_thing(MapThing * thing);

	void place_on_cell(MapThing* thing);

	std::vector<MapThing*> get_floors();
	unsigned int get_number_of_floors();
	MapThing * get_floor(int floor_number);

	bool has_floor();
	void print();

	void clear();

private:

	std::vector<MapThing*>* cell_things;

	void set_i_have_variable(Thing_Type type, bool set_to);

	bool i_have_proyectiles = false;
	bool i_have_enemies = false;
	bool i_have_players = false;
};




