#pragma once
#include "Crazy.h"
#include "PurpleGuy.h"
#include "GreenFatty.h"
#include "Snowball.h"
#include "Fireball.h"
#include "Player.h"
//#include "GraphicObjectFactory.h"

class MapThingFactory
{
public:
	MapThingFactory();
	~MapThingFactory();
	MapThing* create_map_thing(Item_type identifyer, Sense_type direction, void * scenario);
	void register_enemies_event_queue(ALLEGRO_EVENT_QUEUE* ev_queue);
	void register_proyectiles_event_queue(ALLEGRO_EVENT_QUEUE* ev_queue);

private:
	unsigned int get_enemy_id();
	unsigned int get_player_id();
	unsigned int get_proyectile_id();
	unsigned int get_nothing_id();
	unsigned int get_wall_id();

	static unsigned int next_enemy_id;
	static unsigned int next_player_id;
	static unsigned int next_proyectile_id;

	ALLEGRO_EVENT_QUEUE * enemies_ev_queue;
	ALLEGRO_EVENT_QUEUE * proyectiles_ev_queue;

	//GraphicObjectFactory graph_factory;
};


