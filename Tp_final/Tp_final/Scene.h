#pragma once
#include "Userdata.h"
#include "Allegroclass.h"
#include "EventGenerator.h"
#include "EventPackage.h"
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
	void gameInit();

	void handle_movement(Character_id char_id, unsigned int id, Direction_type dir, Action_type action);
	void load_maps();

	bool should_init();
	bool game_is_finished();
	void finish_game();
	//void start_game();
	bool is_the_action_possible(Package* package_to_be_analyze);
	bool should_the_action_be_checked();
	Package* give_me_my_checked_package();
	bool do_you_have_to_draw();

	std::vector <Map*> maps;
	//std::vector<Map*>::iterator actual_map;
	unsigned int actual_map;
private:

	std::vector <Player*> players;





	bool game_started;
	bool game_finished;
	bool check_action;		//see where this flag is turn on or off
	bool has_to_draw;
	Package* package_to_be_appended;

};

