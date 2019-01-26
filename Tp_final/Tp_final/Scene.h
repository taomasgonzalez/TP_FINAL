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

	EventPackage * give_me_my_allegro_event();
	Character_type give_me_my_player();
	Character_type give_the_other_player();
	void set_new_allegro_event(EventPackage * new_event);
	bool game_is_finished();
	void finish_game();
	bool is_the_action_possible(EventPackage* package_to_be_analyze);
	bool check_action(EventPackage * package_to_be_analyze);
	bool do_you_have_to_draw();

	const char * give_me_the_CSV(unsigned int actual_map);


	std::vector <Map*> maps;
	//std::vector<Map*>::iterator actual_map;  //aprender a usarlo bien
	unsigned int actual_map;

	bool game_started;
	bool game_finished;
	//para chequear un evento INTERNO de allegro por ejemplo, se usa en ScenarioEventsObserver::update()
	//hay que prenderlo y hacer notify_obs de scene cuando se levante un evento de allegro, tiene que estar cargado ese
	//evento de allegro convertido en eventpackage en Scene::Package* action_from_allegro;
	bool check_local_action;		//see where this flag is turn on or off
	bool has_to_draw;

private:

	EventPackage* action_from_allegro; //se lo guarda cuando se llama a draw, no esta chequeado. Se lo manda despues a ScenarioEventsObserver::update() para chquearlo
	std::vector <Player*> players;
	Character_type my_player;
	Character_type other_player;






};

