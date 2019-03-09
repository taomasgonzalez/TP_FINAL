#pragma once
#include "Crazy.h"
#include "PurpleGuy.h"
#include "GreenFatty.h"
#include "Snowball.h"
#include "Fireball.h"
#include "Player.h"

class MapThingFactory : public Observable
{
public:
	MapThingFactory();
	~MapThingFactory();
	MapThing* create_map_thing(Item_type identifyer, Sense_type direction, void * scenario);
	void register_enemies_event_queue(ALLEGRO_EVENT_QUEUE* ev_queue);
	void register_proyectiles_event_queue(ALLEGRO_EVENT_QUEUE* ev_queue);
	MapThing* get_last_created_map_thing();

	struct observer_info {
		bool new_map_thing = false;
	};

	observer_info obs_info;

private:
	unsigned int get_enemy_id();
	unsigned int get_player_id();
	unsigned int get_proyectile_id();
	unsigned int get_nothing_id();
	unsigned int get_wall_id();

	unsigned int next_enemy_id;
	unsigned int next_player_id;
	unsigned int next_proyectile_id;

	ALLEGRO_EVENT_QUEUE * enemies_ev_queue;
	ALLEGRO_EVENT_QUEUE * proyectiles_ev_queue;

	MapThing* last_created_map_thing = NULL;

};


