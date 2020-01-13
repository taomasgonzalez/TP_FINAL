#include "MapThingFactory.h"
#include "Scene.h"
#include "DRAW.h"
#include "PlayerSceneObserver.h"
#include "PurpleGuyScenarioObserver.h"
#include "ProyectileSceneObserver.h"

#define MAX_NUMBER_OF_MONSTERS 256
#define MAX_NUMBER_OF_PLAYERS 2
#include <limits>

MapThingFactory::MapThingFactory()
{
	//cada vez que creo una instancia nueva, se reinicia la cuenta para la clase entera.
	next_enemy_id = 0;
	next_proyectile_id = MAX_NUMBER_OF_MONSTERS + MAX_NUMBER_OF_PLAYERS;
}


MapThingFactory::~MapThingFactory()
{
}
MapThing* MapThingFactory::create_map_thing(int fil, int col, Item_type identifyer, Sense_type direction, void * obs_info)
{
	Scene* scene = (Scene*)obs_info;
	MapThing* new_born = nullptr;
	switch (identifyer) {
		case Item_type::NADA:
			new_born = new MapThing(get_nothing_id(), true, Sense_type::None);
			break;
		case Item_type::FLOOR:
			new_born = new MapThing(get_wall_id(), false, Sense_type::None);
			break;
		case Item_type::CRAZY: {
			Crazy* crazy = new Crazy(get_enemy_id(), direction);
			crazy->ev_handler->get_fsm()->add_observer(new EnemySceneObserver(crazy, scene));
			new_born = crazy;
		}
			break;
		case Item_type::GREEN_FATTIE:{
			GreenFatty * green_fatty = new GreenFatty(get_enemy_id(), direction);
			green_fatty->ev_handler->get_fsm()->add_observer(new EnemySceneObserver(green_fatty, scene));
			new_born = green_fatty;
		}
			break;
		case Item_type::PURPLE_GUY: {
			PurpleGuy * purple_guy = new PurpleGuy(get_enemy_id(), direction);
			purple_guy->ev_handler->get_fsm()->add_observer(new PurpleGuyScenarioObserver(purple_guy, scene));
			new_born = purple_guy;
		}
			break;
		case Item_type::TOM:
			Player * play;
			play = new Player((unsigned int)Item_type::TOM, false, direction);
			play->ev_handler->get_fsm()->add_observer(new PlayerSceneObserver(play, scene));
			new_born = play;
			break;
		case Item_type::NICK:
			play = new Player((unsigned int)Item_type::NICK, true, direction);
			play->ev_handler->get_fsm()->add_observer(new PlayerSceneObserver(play, scene));
			new_born = play;
			break;
		case Item_type::FIREBALL:
			Fireball * fire;
			fire = new Fireball(get_proyectile_id(), direction);
			fire->ev_handler->get_fsm()->add_observer(new ProyectileSceneObserver(fire, scene));
			new_born = fire;
			break;
		case Item_type::SNOWBALL:
			Snowball * snow;
			snow = new Snowball(get_proyectile_id(), direction);
			snow->ev_handler->get_fsm()->add_observer(new ProyectileSceneObserver(snow, scene));
			new_born = snow;
			break;
	}

	new_born->pos_x = fil;
	new_born->pos_y = col;

	last_created_map_thing = new_born;
	this->obs_info.new_map_thing = true;
	notify_obs();
	this->obs_info.new_map_thing = false;

	if (identifyer == Item_type::FIREBALL)
		static_cast<Fireball*>(new_born)->ev_handler->get_fsm()->notify_obs();
	else if (identifyer == Item_type::SNOWBALL)
		static_cast<Snowball*>(new_born)->ev_handler->get_fsm()->notify_obs();

	return new_born;
}



void MapThingFactory::register_proyectiles_event_queue(ALLEGRO_EVENT_QUEUE * ev_queue)
{
	proyectiles_ev_queue = ev_queue;
}


unsigned int MapThingFactory::get_enemy_id()
{
	if (next_enemy_id == (unsigned int)Item_type::TOM || next_enemy_id == (unsigned int)Item_type::NICK)
		next_enemy_id++;

	return next_enemy_id++;
}

unsigned int MapThingFactory::get_proyectile_id()
{
	next_proyectile_id++;
	return next_proyectile_id - 1;
}

unsigned int MapThingFactory::get_nothing_id() {
	return std::numeric_limits<unsigned int>::max();
}

unsigned int MapThingFactory::get_wall_id()
{
	return std::numeric_limits<unsigned int>::max() - 1;
}


MapThing* MapThingFactory::get_last_created_map_thing() {
	return last_created_map_thing;
}
