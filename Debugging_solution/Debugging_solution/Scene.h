#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Map.h"

class Scene
{
public:
	Scene();
	~Scene();

	bool action_is_possible();
	void print_current_map();
	void reset_game();
	void load_on_map(char * map_string);
private:

	std::vector <Enemy*> enemies;
	std::vector <Player*> players;
	std::vector<Snowball*> snowballs;
	std::vector<Fireball*> fireballs;

	Map * map;

	static bool game_finished;
};

