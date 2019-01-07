#pragma once
#include "MapThing.h"
#include <vector>
class MapCell
{
public:
	MapCell();
	~MapCell();

	bool has_enemies();
	bool get_enemies();

	bool has_players();
	bool get_players();

	bool has_proyectiles();
	bool get_proyectiles();

private:
	std::vector<MapThing*> cell_things;
};

