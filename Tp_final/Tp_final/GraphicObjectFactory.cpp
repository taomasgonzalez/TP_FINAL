#include "GraphicObjectFactory.h"



GraphicObjectFactory::GraphicObjectFactory()
{
}


GraphicObjectFactory::~GraphicObjectFactory()
{
}

Obj_Graf * GraphicObjectFactory::create_graphic_object(Item_type identifyer, unsigned int id)
{
	Obj_Graf * new_born = NULL;
	switch (identifyer) {
		case Item_type::NADA:
			//new_born = new Obj_Graf();
			break;
		case Item_type::FLOOR:
			//new_born = new Obj_Graf();
			break;
		case Item_type::CRAZY:
			new_born = new Obj_Graf_Enemy(id, CRAZY);
			break;
		case Item_type::GREEN_FATTIE:
			new_born = new Obj_Graf_Enemy(id, FATTY);
			break;
		case Item_type::PURPLE_GUY:
			new_born = new Obj_Graf_Enemy(id, PURPLE);
			break;
		case Item_type::TOM:
			new_born = new Obj_Graf_Player(id, TOM);
			break;
		case Item_type::NICK:
			new_born = new Obj_Graf_Player(id, NICK);
			break;
		case Item_type::FIREBALL:
			new_born = new Obj_Graf_Projectile(id, FIRE);
			break;
		case Item_type::SNOWBALL:
			new_born = new Obj_Graf_Projectile(id, SNOW);
			break;
	}
	return new_born;
}
