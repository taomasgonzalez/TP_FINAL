#include "MapThingFactoryDRAWObserver.h"


Direction get_graph_direction(Sense_type sense);

MapThingFactoryDRAWObserver::MapThingFactoryDRAWObserver(MapThingFactory* factory)
{
	this->drawer = Userdata::drawer;
	this->factory = factory;
}


MapThingFactoryDRAWObserver::~MapThingFactoryDRAWObserver()
{
}

void MapThingFactoryDRAWObserver::update() {
	if (factory->obs_info.new_map_thing) {
		MapThing* last_created_map_thing = factory->get_last_created_map_thing();
		int pos_x = last_created_map_thing->pos_x;
		int pos_y = last_created_map_thing->pos_y;
		Direction dir = get_graph_direction(last_created_map_thing->get_sense());
		unsigned int id = last_created_map_thing->id;

		switch (last_created_map_thing->get_printable())
		{
		case Item_type::TOM:
			drawer->createObjGraf(id, TOM);
			drawer->startDraw(player_IDLE, id, dir, pos_x, pos_y);
			break;
		case Item_type::NICK:
			drawer->createObjGraf(id, NICK);
			drawer->startDraw(player_IDLE, id, dir, pos_x, pos_y);
			break;
		case Item_type::PURPLE_GUY:
			drawer->createObjGraf(id, PURPLE);
			drawer->startDraw(enemy_IDLE, id, dir, pos_x, pos_y);
			break;
		case Item_type::CRAZY:
			drawer->createObjGraf(id, CRAZY);
			drawer->startDraw(enemy_IDLE, id, dir, pos_x, pos_y);
			break;
		case Item_type::GREEN_FATTIE:
			drawer->createObjGraf(id, FATTY);
			drawer->startDraw(enemy_IDLE, id, dir, pos_x, pos_y);
			break;
		case Item_type::FIREBALL:
			drawer->createObjGraf(id, FIRE);
			drawer->startDraw(proy_MOVING, id, dir, pos_x, pos_y);
			break;
		case Item_type::SNOWBALL:
			drawer->createObjGraf(id, SNOW);
			drawer->startDraw(proy_MOVING, id, dir, pos_x, pos_y);
			break;
		}
	}
}

Direction get_graph_direction(Sense_type sense) {
	Direction returnable = Direction::None;
	switch (sense) {
	case Sense_type::Left:
		returnable = Direction::Left;
		break;
	case Sense_type::Right:
		returnable = Direction::Right;
		break;
	default:
		returnable = Direction::None;
		break;
	}
	return returnable;
}
