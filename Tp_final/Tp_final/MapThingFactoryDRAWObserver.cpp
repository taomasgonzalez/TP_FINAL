#include "MapThingFactoryDRAWObserver.h"



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
		switch (last_created_map_thing->get_printable())
		{
			case Item_type::TOM:
				drawer->createObjGraf(last_created_map_thing->id, TOM);
				break;
			case Item_type::NICK:
				drawer->createObjGraf(last_created_map_thing->id, NICK);
				break;
			case Item_type::PURPLE_GUY:
				drawer->createObjGraf(last_created_map_thing->id, PURPLE);
				break;
			case Item_type::CRAZY:
				drawer->createObjGraf(last_created_map_thing->id, CRAZY);
				break;
			case Item_type::GREEN_FATTIE:
				drawer->createObjGraf(last_created_map_thing->id, FATTY);
				break;
			case Item_type::FIREBALL:
				drawer->createObjGraf(last_created_map_thing->id, FIRE);
				break;
			case Item_type::SNOWBALL:
				drawer->createObjGraf(last_created_map_thing->id, SNOW);
				break;
		}
	}
}
