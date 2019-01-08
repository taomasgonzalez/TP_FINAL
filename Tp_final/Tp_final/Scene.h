#pragma once
#include "Userdata.h"
#include "Allegroclass.h"
#include "Enemy.h"
#include "Player.h"
#include "Observable.h"
#include "Map.h"
#include "general.h"

class Scene : public Observable
{
public:
	Scene();
	~Scene();
	void gameInit(Userdata& Userdata, infoType * mydata);

	void handle_movement(Character_id char_id, unsigned int id, Direction dir, Action_type action);
	char * give_me_the_original_map();

	static bool game_is_finished();
	static void finish_game();
	bool should_init;
	void start_game();
	bool action_is_possible();
private:

	std::vector <Enemy*> enemies;
	std::vector <Player*> players;
	std::vector<Snowball*> snowballs;
	std::vector<Fireball*> fireballs;

	Map map;

	char original_map_distribution[192]; //loading the map is pending, reserve memory

	static bool game_finished;
};

