#pragma once
#include "Crazy.h"
#include "PurpleGuy.h"
#include "GreenFatty.h"
#include "Snowball.h"
#include "Fireball.h"
#include "Player.h"

class MapThingFactory
{
public:
	MapThingFactory();
	~MapThingFactory();
	MapThing* create_map_thing(char identifyer);
private:
	unsigned int get_enemy_id();
	unsigned int get_player_id();
	unsigned int get_proyectile_id();
	unsigned int get_nothing_id();
	unsigned int get_wall_id();

	static unsigned int next_enemy_id;
	static unsigned int next_player_id;
	static unsigned int next_proyectile_id;
};


