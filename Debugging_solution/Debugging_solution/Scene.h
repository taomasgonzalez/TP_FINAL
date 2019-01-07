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

	void handle_movement(Character_id char_id, unsigned int id, Direction dir, Action action);

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

	static bool game_finished;
};

