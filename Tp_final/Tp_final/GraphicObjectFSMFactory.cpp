#include "GraphicObjectFSMFactory.h"

#include "GraphicObjectFSMDRAWObserver.h"
#include "GraficObjectProjectile.h"
#include "GraficObjectEnemy.h"
#include "GraficObjectPlayer.h"
#include "GraficObjectBall.h"

GraphicObjectFSMFactory::GraphicObjectFSMFactory(Userdata* data)
{
	this->data = data;

}


GraphicObjectFSMFactory::~GraphicObjectFSMFactory()
{
}

GraphicObjectFSM * GraphicObjectFSMFactory::create_graphic_fsm(Item_type identifyer, unsigned int id)
{
	GraphicObjectFSM * new_born = NULL;
	switch (identifyer) {
		case Item_type::NADA:
			//new_born = new Obj_Graf();
			break;
		case Item_type::FLOOR:
			//new_born = new Obj_Graf();
			break;
		case Item_type::CRAZY:
			new_born = new GraphicObjectFSM(data, id, identifyer, drawer->createObjGraf(id,CRAZY), drawer);
			break;
		case Item_type::GREEN_FATTIE:
			new_born = new GraphicObjectFSM(data, id, identifyer, drawer->createObjGraf(id, FATTY), drawer);
			break;
		case Item_type::PURPLE_GUY:
			new_born = new GraphicObjectFSM(data, id, identifyer, drawer->createObjGraf(id, PURPLE), drawer);
			break;
		case Item_type::TOM:
			new_born = new GraphicObjectFSM(data, id, identifyer, drawer->createObjGraf(id, TOM), drawer);
			break;
		case Item_type::NICK:
			new_born = new GraphicObjectFSM(data, id, identifyer, drawer->createObjGraf(id, NICK), drawer);
			break;
		case Item_type::FIREBALL:
			new_born = new GraphicObjectFSM(data, id, identifyer, drawer->createObjGraf(id, FIRE), drawer);
			break;
		case Item_type::SNOWBALL:
			new_born = new GraphicObjectFSM(data, id, identifyer, drawer->createObjGraf(id, SNOW), drawer);
			break;
	}

	new_born->add_observer(new GraphicObjectFSMDRAWObserver(new_born, drawer));
	return new_born;
}



void GraphicObjectFSMFactory::append_graphic_facility(void * drawer)
{
	this->drawer = (DRAW*) drawer;
}
