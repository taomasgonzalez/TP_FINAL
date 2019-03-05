#include "ScenarioDRAWObserver.h"


ScenarioDRAWObserver::ScenarioDRAWObserver(Scene* scenario, DRAW* drawer)
{
	this->scenario = scenario;
	this->drawer = drawer;
}


ScenarioDRAWObserver::~ScenarioDRAWObserver()
{
}

void ScenarioDRAWObserver::update() {
	/*
	if (scenario->new_character) {
		Character* lastly_created_character = scenario->get_lastly_created_character();
		lastly_created_character->add_observer(new CharacterDRAWObserver(lastly_created_character, drawer));
		switch (lastly_created_character->get_printable())
		{
		case Item_type::TOM:
			drawer->createObjGraf(lastly_created_character->id, TOM);
			break;
		case Item_type::NICK:
			drawer->createObjGraf(lastly_created_character->id, NICK);
			break;
		case Item_type::PURPLE_GUY:
			drawer->createObjGraf(lastly_created_character->id, PURPLE);
			break;
		case Item_type::CRAZY:
			drawer->createObjGraf(lastly_created_character->id, CRAZY);
			break;
		case Item_type::GREEN_FATTIE:
			drawer->createObjGraf(lastly_created_character->id, FATTY);
			break;
		case Item_type::FIREBALL:
			drawer->createObjGraf(lastly_created_character->id, FIRE);
			break;
		case Item_type::SNOWBALL:
			drawer->createObjGraf(lastly_created_character->id, SNOW);
			break;
		}
			
	}
	*/
	if (scenario->load_graphic_level) {
		drawer->add_level(scenario->give_me_the_map_info());
	}
}
