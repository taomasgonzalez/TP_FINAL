#pragma once
#include "Userdata.h"
#include "Allegroclass.h"
#include "EventGenerator.h"
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
	void gameInit(Userdata& Userdata);

	void handle_movement(Character_id char_id, unsigned int id, Direction dir, Action_type action);
	char * give_me_the_original_map();

	static bool game_is_finished();
	static void finish_game();
	bool should_init;
	void start_game();
	bool action_is_possible(EventPackage* package_to_be_analyze);
	bool should_the_action_be_checked();
	EventPackage* give_me_my_checked_package();

private:

	std::vector <Enemy*> enemies;
	std::vector <Player*> players;
	std::vector<Snowball*> snowballs;
	std::vector<Fireball*> fireballs;

	Map map;

	char original_map_distribution[192]; //loading the map is pending, reserve memory

	static bool game_finished;

	bool check_action;		//see where this flag is turn on or off
	EventPackage* package_to_be_appended;

};

