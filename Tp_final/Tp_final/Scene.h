#pragma once
#include "Userdata.h"
#include "Allegroclass.h"
#include "Enemy.h"
#include "Player.h"
#include "Observable.h"
#include "Scene.h"
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
	static void start_game();
private:
	std::vector <Enemy*> enemies;
	std::vector <Player*> players;

	Map map;


	static bool game_finished;
};

