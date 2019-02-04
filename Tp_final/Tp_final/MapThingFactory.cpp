#include "MapThingFactory.h"

#define MAX_NUMBER_OF_MONSTERS 256
#define MAX_NUMBER_OF_PLAYERS 2
#include <limits>

MapThingFactory::MapThingFactory()
{
	//cada vez que creo una instancia nueva, se reinicia la cuenta para la clase entera.
	next_enemy_id = 0;
	next_player_id = next_enemy_id + MAX_NUMBER_OF_MONSTERS;
	next_proyectile_id = next_player_id + MAX_NUMBER_OF_PLAYERS;
}


MapThingFactory::~MapThingFactory()
{
}

MapThing * MapThingFactory::create_map_thing(Item_type identifyer, Sense_type direction)
{
	MapThing* new_born = nullptr;
	switch (identifyer) {
	case Item_type::NADA:
			new_born = new MapThing(get_nothing_id(), true);
			break;
		case Item_type::FLOOR:
			new_born = new MapThing(get_wall_id(), false);
			break;
		case Item_type::CRAZY:
			new_born = new Crazy(get_enemy_id());
			break;
		case Item_type::GREEN_FATTIE:
			new_born = new GreenFatty(get_enemy_id());
			break;
		case Item_type::PURPLE_GUY:
			new_born = new PurpleGuy(get_enemy_id());
			break;
		case Item_type::TOM:
			new_born = new Player(get_player_id());
			new_born->set_printable(Item_type::TOM);
			break;
		case Item_type::NICK:
			new_born = new Player(get_player_id());
			new_born->set_printable(Item_type::NICK);
			break;
		case Item_type::FIREBALL:
			new_born = new Fireball(get_proyectile_id());
			break;
		case Item_type::SNOWBALL:
			new_born = new Snowball(get_proyectile_id());

			break;
	}
	if (new_born->is_enemy())
		al_register_event_source(enemies_ev_queue, al_get_timer_event_source(((Enemy*)new_born)->get_acting_timer()));

	return new_born;
}

void MapThingFactory::register_enemies_event_queue(ALLEGRO_EVENT_QUEUE* ev_queue)
{
	enemies_ev_queue = ev_queue;
}


unsigned int MapThingFactory::get_enemy_id()
{
	next_enemy_id++;
	return next_enemy_id-1;
}

unsigned int MapThingFactory::get_player_id()
{
	next_player_id++;
	return next_player_id - 1;
}

unsigned int MapThingFactory::get_proyectile_id()
{
	next_proyectile_id++;
	return next_player_id - 1;
}

unsigned int MapThingFactory::get_nothing_id() {
	return std::numeric_limits<unsigned int>::max();
}

unsigned int MapThingFactory::get_wall_id()
{
	return std::numeric_limits<unsigned int>::max() - 1;
}


unsigned int MapThingFactory::next_enemy_id;
unsigned int MapThingFactory::next_player_id;
unsigned int MapThingFactory::next_proyectile_id;