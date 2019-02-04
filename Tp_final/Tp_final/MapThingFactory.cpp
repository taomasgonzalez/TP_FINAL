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

MapThing * MapThingFactory::create_map_thing(char identifyer)
{
	MapThing* new_born = nullptr;
	switch (identifyer) {
		case 'E':
			new_born = new MapThing(get_nothing_id(), true);
			break;
		case 'F':
			new_born = new MapThing(get_wall_id(), false);
			break;
		case 'C':
			new_born = new Crazy(get_enemy_id());
			break;
		case 'G':
			new_born = new GreenFatty(get_enemy_id());
			break;
		case 'P':
			new_born = new PurpleGuy(get_enemy_id());
			break;
		case 'T':
			new_born = new Player(get_player_id());
			new_born->set_printable('T');
			break;
		case 'N':
			new_born = new Player(get_player_id());
			new_born->set_printable('N');
			break;
		case 'B':
			new_born = new Fireball(get_proyectile_id());
			break;
		case 'S':
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